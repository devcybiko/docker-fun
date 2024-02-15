#ifndef __NODE__
#define __NODE__

#include "Object.h"

#define ParentClass ObjectClass
#define _ParentClass _ObjectClass
#define PARENT_METHODS OBJECT_METHODS
#define PARENT_MEMBERS OBJECT_MEMBERS

typedef struct Node Node;

#define NEW_METHODS \
    void (*initNode)(void *this, char *name, Node *parent);

#define NEW_MEMBERS \
    Node *parent; \
    Node *children;

NEW_CLASS(NodeClass, _NodeClass, _NodeParent)
NEW_OBJECT(Node, NodeClass)

Node *newNode(char *name, Node *parent);

#endif // __NODE__
