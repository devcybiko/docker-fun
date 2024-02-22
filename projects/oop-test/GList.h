#ifndef __LIST__
#define __LIST__

#include "GObj.h"

#define GList_MEMBERS(Obj, SuperObj) \
    void **array; \
    int extent; \
    int size; \
    double mult; \

#define GList_CONSTRUCTOR(Obj, SuperObj) \
    Obj *(*new)(char *name, int extent, double mult); \
    CLASS_NAME(Obj) *(*init)(char *name, int extent, double mult); 

#define GList_METHODS(Obj, SuperObj) \
    GListClass *(*push)(void *value); \
    void *(*get)(int n);


CLASS(GList, GObj)

#endif // __LIST__
