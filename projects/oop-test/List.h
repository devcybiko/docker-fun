#ifndef _LIST_
#define _LIST_

#include "Object.h"

typedef struct ListClass ListClass;
typedef struct ListObj ListObj;

typedef struct ListObj {
    Object *obj;
    char **list_array;
    int list_extent;
    int list_size;
    double list_mult;
} ListObj;

typedef struct ListClass {
    ObjectClass *Object;
    ListObj *(*new)(char *name, int extent, double mult);
    void (*destroy)(ListObj *obj);
    ListClass *(*init)(ListObj *obj, char *name, int extent, double mult);
    ListClass *(*debug)(ListObj *obj, char *args);
    ListClass *(*push)(ListObj *, char *value);
    char *(*get)(ListObj *this, int n);
} ListClass;

ListClass *getListClass();

#endif // _NODE_
