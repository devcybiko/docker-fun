#include <stdio.h>
#include <assert.h>

#include "../psil_memory.h"

void println(char *fmt, void *args)
{
    printf(fmt, args);
    printf("\n");
}
void iprintln(char *fmt, int args)
{
    printf(fmt, args);
    printf("\n");
}

void test_PMemoryNew()
{
    println(">> test_PMemoryNew", 0);
    PMemory *pm = PMemoryNew(100, 10);
    assert(pm->nbytes == 100);
    assert(pm->reftab->nblobs == 10);
    PMemoryDestroy(pm);
}

// void test_PBlobNew() {
//      this creates an empty blog without a ref entry
//     println(">> test_PBlobNew", 0);
//     PMemory *pm = PMemoryNew(100, 10);
//     POffset offset = PBlobNew(pm, 5);
//     iprintln("... offset = %d", offset);
//     _PMemoryPrint(pm);
//     PMemoryDestroy(pm);
// }

void test_PRefAlloc_too_little_memory()
{
    println(">> test_PRefAlloc", 0);
    PMemory *pm = PMemoryNew(100, 10);
    PRef ref = PRefAlloc(pm, 5);
    assert(ref == 1);
    ref = PRefAlloc(pm, 20);
    assert(ref == -1);
    _PMemoryPrint(pm);
    PMemoryDestroy(pm);
}

void test_PRefAlloc()
{
    println(">> test_PRefAlloc", 0);
    PMemory *pm = PMemoryNew(1000, 10);
    PRef ref = PRefAlloc(pm, 5);
    assert(ref == 1);
    ref = PRefAlloc(pm, 20);
    assert(ref == 2);
    _PMemoryPrint(pm);
    PMemoryDestroy(pm);
}

int main()
{
    printf("Testing PSIL!\n");
    test_PMemoryNew();
    // test_PBlobNew();
    test_PRefAlloc();
    test_PRefAlloc_too_little_memory();
    printf("PASSED PSIL!\n");
    return 0;
}
