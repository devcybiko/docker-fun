#ifndef __GObj__
#define __GObj__

#include "Template.h"
#include "GDefines.h"

extern void *_THIS; // this
extern void *_this(); // _this

#define GObj_CLASS \
    char name[16];\
    METHOD(GObj *, init)();\
    METHOD(GObj *, delete)();\
    METHOD(void , debug)(char *message);\
    METHOD(char *, toString)();

ROOT_CLASS(GObj)

extern GObj *GObj_new(char *name);

#endif // __GObj__
