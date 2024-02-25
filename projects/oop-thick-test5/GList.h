#ifndef __GList__
#define __GList__

#include "GObj.h"

// echo -n "GList" | xxd -ps
// 474c697374
#define GList_ID 0x474c697374

CLASS(GList)
    GObj_CLASS
    GObj **array;
    int extent;
    int size;
    double mult;
    bool safe;

    METHOD(void, push)(GObj *value);
    METHOD(GObj *, get)(int n);
    METHOD(int, set)(int n, GObj *value);
    METHOD(void, safeDelete)();
} GList;

GList *GList_new();
GList *GList_new_full(char *name, int extent, double mult);

#endif // __GList__