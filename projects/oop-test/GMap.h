#ifndef __GMAP__
#define __GMAP__

#include "GObj.h"
#include "GList.h"

typedef struct GMapClass GMapClass;

typedef struct GEntry {
    char *key;
    void *value;
} GEntry;

typedef struct GMap {
    GNAME name;
    GMapClass *class;
    GObjClass *super;
    GList *list;
} GMap;

typedef struct GMapClass {
    GMap *(*new)(char *name);
    GMapClass *(*init)(char *name);
    void (*destroy)();
    GMapClass *(*debug)(char *args);
    GMapClass *(*put)(char *key, void *value);
    void *(*get)(char *key);
    GEntry *(*getEntry)(char *key);
    GMapClass *(*putEntries)(GEntry *entries);
} GMapClass;

extern GMapClass *GMap$;

#endif // __GMAP__
