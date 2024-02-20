#ifndef __LIST__
#define __LIST__

#include "GObj.h"

typedef struct GListClass GListClass;

typedef struct GList {
    GNAME name;
    void **array;
    int extent;
    int size;
    double mult;
} GList;

typedef struct GListClass {
    GList *(*new)(char *name, int extent, double mult);
    void (*destroy)(GList *obj);
    GListClass *(*init)(GList *obj, char *name, int extent, double mult);
    GListClass *(*debug)(GList *obj, char *args);
    GListClass *(*push)(GList *, void *value);
    void *(*get)(GList *this, int n);
} GListClass;

extern GListClass *GLIST;

#endif // __LIST__
