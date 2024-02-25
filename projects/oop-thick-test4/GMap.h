#ifndef __GMap__
#define __GMap__

#include "GObj.h"
#include "GList.h"

typedef struct GEntry {
    char * key;
    void *value;
} GEntry;

// echo -n "GMap" | xxd -ps
// 474d6170
#define GMap_ID 0x474d6170

CLASS(GMap)
    int id;
    GObj *obj;
    GList *list;

    METHOD(void, delete)();
    METHOD(void , debug)(char *message);
    METHOD(char *, toString)();
    METHOD(void, put)(char * key, void *value);
    METHOD(void *, get)(char * key);
    METHOD(GEntry *, getEntry)(char * key);
    METHOD(void, putEntries)(GEntry *entries);
CLASS_END(GMap);

GMap *GMap_new(char *name);

#endif // __GMap__