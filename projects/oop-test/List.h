#ifndef _LIST_
#define _LIST_

#include "Object.h"

#define ParentClass ObjectClass
#define _ParentClass _ObjectClass
#define PARENT_METHODS OBJECT_METHODS
#define PARENT_MEMBERS OBJECT_MEMBERS

typedef struct ListClass ListClass;
typedef struct ListInstance ListInstance;

#define NEW_METHODS \
    void (*push)(void *this, void *value);\
    void *(*get)(void *this, int n);

#define NEW_MEMBERS \
    void **list_array; \
    int list_extent; \
    int list_size;

NEW_CLASS(ListClass, getListClass, ListInstance)
NEW_INSTANCE(ListInstance)

#endif // _NODE_
