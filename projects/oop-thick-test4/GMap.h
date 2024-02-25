#ifndef __GMap__
#define __GMap__

#include "GObj.h"
#include "GList.h"

typedef struct GEntry {
    char * key;
    void *value;
} GEntry;

#define GMap_CLASS \
    GList *list; \
\
    METHOD(void, put)(char * key, void *value);\
    METHOD(void *, get)(char * key);\
    METHOD(GEntry *, getEntry)(char * key);\
    METHOD(void, putEntries)(GEntry *entries);

CLASS(GMap, GObj)

GMap *GMap_new(char *name);

#endif // __GMap__