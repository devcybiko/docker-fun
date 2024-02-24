#ifndef __GObj__
#define __GObj__

#include "GDefines.h"

extern void *THIS; // this

typedef struct GObj GObj;

typedef struct GObj {
    // members
    char name[16];

    // methods
    GObj *(*init)(char *name);
    GObj *(*delete)();
    void (*debug)(char *message);
    char *(*toString)();
} GObj;

extern GObj *GObj_new(char *name);

#endif // __GObj__
