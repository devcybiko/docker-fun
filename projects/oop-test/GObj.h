#ifndef __OBJECT__
#define __OBJECT__

#include "GDefines.h"

#define GObj_MEMBERS(Obj, SuperObj) \
    GNAME name; \
    CLASS_NAME(Obj) *class; \
    CLASS_NAME(SuperObj) *super;

#define GObj_CONSTRUCTOR(Obj, SuperObj) \
    Obj *(*new)(char *name); \
    CLASS_NAME(Obj) *(*init)(char *name); 

#define GObj_METHODS(Obj, SuperObj) \
    void (*destroy)(); \
    CLASS_NAME(Obj) *(*debug)(char *args);

_CLASS(GObj)

#endif // __OBJECT__
