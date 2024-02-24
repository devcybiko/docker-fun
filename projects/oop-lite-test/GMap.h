#ifndef __GMAP__
#define __GMAP__

#include "GObj.h"
#include "GList.h"

typedef struct GEntry {
    char *key;
    void *value;
} GEntry;

#define GMap_MEMBERS(Obj, SuperObj) \
    GList *list;

#define GMap_CONSTRUCTOR(Obj, SuperObj) \
    Obj *(*new)(char *name); \
    CLASS_NAME(Obj) *(*init)(char *name);

#define GMap_METHODS(Obj, SuperObj) \
    CLASS_NAME(Obj) *(*put)(char *key, void *value);\
    void *(*get)(char *key);\
    GEntry *(*getEntry)(char *key);\
    CLASS_NAME(Obj) *(*putEntries)(GEntry *entries);

CLASS(GMap, GObj)

#endif // __GMAP__
