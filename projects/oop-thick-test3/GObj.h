#ifndef __GObj__
#define __GObj__

#include "Template.h"
#include "GDefines.h"

extern void *THIS; // this

#define GObj_CLASS \
    char name[16];\
    GObj *(*init)();\
    GObj *(*delete)();\
    void (*debug)(char *message);\
    char *(*toString)();

ROOT_CLASS(GObj)

extern GObj *GObj_new(char *name);

#endif // __GObj__
