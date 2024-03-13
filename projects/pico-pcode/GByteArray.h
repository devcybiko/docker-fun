#ifndef __GByteArray__
#define __GByteArray__

#include "./gtos/GObj.h"

// echo -n "Byte" | xxd -ps
#define GByteArray_ID 0x42797465

#define GByteArray_MEMBERS(Obj, SuperObj) \
    int extent; \
    int used; \
    char *bytes;

#define GByteArray_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id, int extent);

#define GByteArray_METHODS(Obj, SuperObj) \
    METHOD(char *, alloc)(int n);

CLASS(GByteArray, GObj)

extern GByteArray* GByteArray_new(int extent);

#endif // __GByteArray__
