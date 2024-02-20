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
    GList *list;

} GMap;

typedef struct GMapClass {
    GMap *(*new)(char *name);
    void (*destroy)(GMap *obj);
    GMapClass *(*init)(GMap *obj, char *name);
    GMapClass *(*debug)(GMap *obj, char *args);
    GEntry *(*put)(GMap *obj, char *key, void *value);
    void *(*get)(GMap *obj, char *key);
    GEntry *(*find)(GMap *obj, char *key);
    GMapClass *(*addMap)(GMap *obj, GEntry *entries);
} GMapClass;

extern GMapClass *GMAP;

#endif // __GMAP__
