#ifndef __GObj__
#define __GObj__

#include "GDefines.h"

extern void *THIS; // this

typedef struct GObj GObj;

#define GObj_MEMBERS \
    char name[16];

#define GObj_METHODS \
    GObj *(*delete)(); \
    void (*debug)(char *message); \
    char *(*toString)();

#define GObj_CLASS \
    GObj_MEMBERS \
    GObj_METHODS


typedef struct GObj {
    GObj_CLASS
} GObj;

extern GObj *GObj_new(char *name);
extern GObj *GObj_init(GObj *this, char *name);

#endif // __GObj__
