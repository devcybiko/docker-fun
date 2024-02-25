#ifndef __GMap__
#define __GMap__

#include "GObj.h"
#include "GList.h"

// echo -n "GMap" | xxd -ps
// 474d6170
#define GMap_ID 0x474d6170

CLASS(GMap)
    GObj_CLASS
    GList *keys;
    GList *values;

    METHOD(void, put)(char * key, GObj *value);
    METHOD(void *, get)(char * key);
CLASS_END(GMap);

GMap *GMap_new_full(char *name);
GMap *GMap_new();

#endif // __GMap__