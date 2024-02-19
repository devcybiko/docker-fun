#ifndef __NODE__
#define __NODE__

#include "Object.h"
#include "List.h"

typedef struct NodeClass NodeClass;
typedef struct NodeObj NodeObj;

typedef struct NodeObj {
    Object *obj;
    NodeObj *parent;
    ListObj *children;
} NodeObj;

typedef struct NodeClass {
    ObjectClass *Object;
    ListClass *List;
    NodeObj *(*new)(char *name, NodeObj *parent);
    NodeClass *(*destroy)(NodeObj *obj);
    NodeClass *(*init)(NodeObj *obj, char *name, NodeObj *parent);
    NodeClass *(*debug)(NodeObj *obj, char *args);
} NodeClass;

NodeClass *getNodeClass();

#endif // __NODE__
