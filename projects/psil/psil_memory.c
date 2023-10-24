#include <stdlib.h>
#include <stdio.h>
#include "psil_memory.h"

// Memory management

void _debug(char *fmt, void *args)
{
    // printf(fmt, args);
}
void _idebug(char *fmt, int args)
{
    // printf(fmt, args);
}
void _idebug2(char *fmt, int arg0, int arg1)
{
    // printf(fmt, arg0, arg1);
}

int _nbytes(int size)
{
    // round up to the nearest word
    // _idebug(">> _nbytes, size = %d\n", size);
    int nwords = (size + sizeof(PWord) - 1) / sizeof(PWord);
    // _idebug("<< nwords %d\n", nwords);
    return nwords * sizeof(PWord);
}

int _findPBlob(PMemory *pm, int __nbytes)
{
    // simplistic model
    int nbytes = _nbytes(__nbytes + sizeof(PBlob));
    _idebug(">> _findPBlob, nbytes = %d\n", nbytes);
    POffset offset = 0;
    int mindiff = 1000000; // infinity
    POffset imindiff = -1; // index to minimum diff entry
    PFreeBlob *pfb = (PFreeBlob *)&pm->data[offset];
    _idebug(".. extent = %d\n", pfb->extent);
    _debug("pfb = %p\n", pfb);
    do
    {
        int diff = pfb->extent - nbytes;
        _idebug(".. diff = %d\n", diff);
        if (diff >= 0 && diff < mindiff)
        {
            _idebug(".... diff = %d\n", diff);
            _idebug(".... mindiff = %d\n", mindiff);
            _idebug(".... offset = %d\n", offset);
            mindiff = diff;
            imindiff = offset;
            if (diff == 0)
                break;
        }
        offset = pfb->next; // next free blob
    } while (offset);
    _idebug("<< _findPBlob, imindiff = %d\n", imindiff);
    _idebug("<< _findPBlob, imindiff = %d\n", imindiff);
    return imindiff;
}

PRef _findOpenRef(PMemory *pm)
{
    // simplistic model
    PRef ref = 0;
    PRefTab *reftab = pm->reftab;
    for (int i = 0; i < reftab->nblobs; i++)
    {
        if (reftab->offsets[i] == 0)
            return ref;
        ref++;
    }
    return -1; // no space
}

void _PFreeBlobPrint(PFreeBlob *pfb)
{
    printf(".... pfb = %p\n", pfb);
    printf("..... pfb->extent = %d\n", pfb->extent);
    printf("..... pfb->next = %d\n", pfb->next);
}

void _PBlobPrint(PBlob *blob)
{
    printf(".... blob = %p\n", blob);
    printf("..... blob->extent = %d\n", blob->extent);
    printf("..... blob->size = %d\n", blob->size);
    printf("..... blob->ref = %d\n", blob->ref);
    printf("..... blob->_dummy = %p, %d\n",&blob->_dummy, blob->_dummy);
    printf("..... blob->data = %p\n", blob->data);
}

void _PRefTabPrint(PMemory *pm, PRefTab *reftab)
{
    printf("... reftab = %p\n", reftab);
    printf("... reftab->nblobs = %d\n", reftab->nblobs);
    printf("... reftab->offsets = %p\n", reftab->offsets);
    for (int i = 1; i < reftab->nblobs; i++)
    {
        printf("... reftab->offsets[%d] = %d\n", i, reftab->offsets[i]);
        if (reftab->offsets[i])
            _PBlobPrint((PBlob *)&pm->data[reftab->offsets[i]]);
    }
}

void _PMemoryPrint(PMemory *pm)
{
    printf(".. pm = %p\n", pm);
    PFreeBlob *pfb = (PFreeBlob *)&pm->data[0]; // always at offset 0
    printf(".. pm->nbytes = %d\n", pm->nbytes);
    printf(".. pm->data = %p\n", pm->data);
    printf(".. pfb = %p\n", pfb);
    printf(".. pfb->extent = %d\n", pfb->extent);
    printf(".. pfb->next = %d\n", pfb->next);
    _PRefTabPrint(pm, pm->reftab);
}

PMemory *PMemoryNew(int nbytes, int nrefs)
{
    _debug(">> PMemoryNew\n", NULL);
    PMemory *pm = (PMemory *)calloc(1, sizeof(PMemory) + _nbytes(nbytes));
    pm->nbytes = _nbytes(nbytes);
    PFreeBlob *pfb = (PFreeBlob *)&pm->data[0]; // always at offset 0
    pfb->extent = pm->nbytes;                   // free blob extent
    pfb->next = 0;                              // end of free list
    int reftabsize = _nbytes(sizeof(PRefTab) + nrefs * sizeof(POffset));
    _idebug(" .. reftabsize = %d\n", reftabsize);
    POffset reftaboffset = PBlobNew(pm, reftabsize);
    pm->reftab = (PRefTab *)&pm->data[reftaboffset];
    pm->reftab->nblobs = nrefs;
    pm->reftab->offsets[0] = reftaboffset; // first ref points to the reftab itself
    _debug("<< PMemoryNew, %p\n", pm);

    return pm;
}

PMemory *PMemoryDestroy(PMemory *pm)
{
    free(pm);
    return NULL;
}

POffset PBlobNew(PMemory *pm, int nbytes)
{
    _idebug(">> PBlobNew, nbytes = %d\n", nbytes);
    int extent = _nbytes(nbytes);
    int blobSize = _nbytes(sizeof(PBlob) + extent);
    int offset = _findPBlob(pm, blobSize);
    if (offset < 0) {
        return -1; // no space
    }
    // found a free blob
    // split off nbytes from the bottom of the blob
    // and reduce the size of the free blob
    PFreeBlob *pfb = (PFreeBlob *)&pm->data[offset];
    POffset newoffset = pfb->extent - blobSize;
    _idebug("... newoffset = %d\n", newoffset);
    PBlob *blob = (PBlob *)&pm->data[newoffset];
    _debug("... blob = %p\n", blob);
    blob->extent = extent;
    blob->size = 0;
    _PBlobPrint(blob);
    pfb->extent = newoffset;
    pfb->next = 0;
    return newoffset;
}

PRef PRefAlloc(PMemory *pm, int nbytes)
{
    _idebug(">> PRefAlloc, nbytes = %d\n", nbytes);
    int offset = PBlobNew(pm, nbytes); // offset into pm->data
    _idebug("... offset = %d\n", offset);
    if (offset < 0)
        return -1; // no space
    PRef ref = _findOpenRef(pm);
    if (ref < 0)
        return -2; // no refs available
    // found a free blob and a free ref
    // add the blob to the ref table
    pm->reftab->offsets[ref] = offset;
    PBlob *blob = (PBlob *)&pm->data[offset];
    blob->ref = ref;
    return ref;
}