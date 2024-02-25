#ifndef __GList__
#define __GList__

#include "GObj.h"

// echo -n "GList" | xxd -ps
// 474c697374
#define GList_ID 0x474c697374

typedef struct GList GList;
typedef struct GList {
    int id;
    GObj *obj;
    void **array;
    int extent;
    int size;
    double mult;

    METHOD(void, delete)();
    METHOD(void , debug)(char *message);
    METHOD(char *, toString)();
    
    METHOD(void, push)(void *value);
    METHOD(void *, get)(int n);
} GList;

GList *GList_new(char *name, int extent, double mult);

#endif // __GList__