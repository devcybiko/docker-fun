#ifndef __GObj__
#define __GObj__

#include "GDefines.h"

#define GObj_MEMBERS(Obj, SuperObj) \
    GNAME name; \
    CLASS_NAME(Obj) *class; \
    CLASS_NAME(SuperObj) *super;

#define GObj_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(GObj *, new)(char *name); \
    METHOD(CLASS_NAME(Obj) *, init)(char *name);

#define GObj_METHODS(Obj, SuperObj) \
    METHOD(void, delete)(); \
    METHOD(char *, toString)(); \
    METHOD(CLASS_NAME(Obj) *, debug)(char *args);

_CLASS(GObj)

#endif // __GObj__
