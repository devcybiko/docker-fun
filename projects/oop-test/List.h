#ifndef _LIST_
#define _LIST_

#include "Object.h"

typedef struct List List;

typedef struct List {
    Object *obj;
    char **list_array;
    int list_extent;
    int list_size;
    double list_mult;

    void (*destroy)(List *obj);
    List *(*init)(List *obj, char *name, int extent, double mult);
    List *(*debug)(List *obj, char *args);
    List *(*push)(List *, char *value);
    char *(*get)(List *this, int n);
} List;

List *listNew(char *name, int extent, double mult);

#endif // _NODE_
