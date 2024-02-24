#ifndef __GList__
#define __GList__

#include "GObj.h"

#define GList_CLASS \
    void **array; \
    int extent; \
    int size; \
    double mult; \
\
    void (*push)(void *value);\
    void *(*get)(int n);

CLASS(GList, GObj)

GList *GList_new(char *name, int extent, double mult);

#endif // __GList__