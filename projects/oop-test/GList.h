#ifndef __LIST__
#define __LIST__

#include "GObj.h"

typedef struct GListClass GListClass;

typedef struct GList {
    GNAME name;
    GListClass *class;
    GObjClass *super;
    void **array;
    int extent;
    int size;
    double mult;
} GList;

typedef struct GListClass {
    const GObjClass *super;
    GList *(*new)(char *name, int extent, double mult);
    void (*destroy)();
    GListClass *(*init)( char *name, int extent, double mult);
    GListClass *(*debug)( char *args);
    GListClass *(*push)(void *value);
    void *(*get)(int n);
} GListClass;

extern GListClass *GList$;

#endif // __LIST__
