typedef unsigned char PByte; // 8 bit byte
typedef unsigned short PInt; // 16 bit word
typedef unsigned short PWord; // 32 bit word
typedef unsigned int PRef; // 16 bit reference to blob
typedef unsigned int POffset; // 16 bit offset into pm->data for blob

typedef struct preftab {
    PInt nblobs; // the number of blobs in the table
    POffset offsets[]; // array of offsets into pm->data[] for each blob
} PRefTab;

typedef struct pmemory {
    // the entire memory is a single array of bytes
    // we'll allocate blobs of this memory
    PInt nbytes; // the number of bytes in the memory block
    PRefTab *reftab; // offset into data[] for the reference table
    PByte data[]; // [size] byte of data - word-aligned
} PMemory;

typedef struct pfreeblob {
    // a blob that is free and can be allocated
    PInt extent; // size of this free blob in bytes
    PInt next; // index of the next free blob in bytes
} PFreeBlob;

typedef struct pblob {
    PInt extent; // the total size of the blob in bytes
    PInt size; // the number of bytes used, size <= extent
    PInt ref; // the reference index into the PrefTab
    PInt _dummy; // unused
    PByte data[]; // [extent] bytes of data 
} PBlob;

typedef struct pstack {
    PInt size; // the number of words used
    PWord data[]; // [size] words of data
} PStack;

extern PMemory *PMemoryNew(int nbytes, int nrefs);
extern PMemory *PMemoryDestroy(PMemory *pm);
extern POffset PBlobNew(PMemory *pm, int nbytes);
extern PRef PRefAlloc(PMemory *pm, int nbytes);

extern void _PMemoryPrint(PMemory *pm);
