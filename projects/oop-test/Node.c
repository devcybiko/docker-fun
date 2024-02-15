#include "Node.h"

static NodeClass nodeClass;

static NodeClass *nodeDebug(NodeObj *this, char *args) {
    nodeClass.Object->debug(this->obj, args);
    nodeClass.List->debug(this->children, NULL);
    printf("Node.parent: %p\n", this->parent);
    return &nodeClass;
}

static NodeClass *nodeDestroy(NodeObj *this) {
    DEBUG("    > nodeDestroy\n");
    nodeClass.Object->destroy(this->obj);
    nodeClass.List->destroy(this->children);
    free(this);
    DEBUG("    < nodeDestroy\n");
    return &nodeClass;
}

static NodeClass *nodeInit(NodeObj *this, char *name, NodeObj *parent) {
    DEBUG("    > nodeInit\n");
    this->obj = nodeClass.Object->new(name);
    this->parent = parent;
    this->children = nodeClass.List->new("List", 16, 0);
    DEBUG("    < nodeInit\n");
    return &nodeClass;
}

static NodeObj *nodeNew(char *name, NodeObj *parent) {
    DEBUG("  > nodeNew\n");
    NodeObj *this = NEW(NodeObj);
    nodeClass.init(this, name, parent);
    DEBUG("  < nodeNew\n");
    return this;
}

NodeClass *getNodeClass()
{
    DEBUG("  > getNode\n");
    nodeClass.Object = getObjectClass();
    nodeClass.List = getListClass();
    nodeClass.new = nodeNew;
    nodeClass.init = nodeInit;
    nodeClass.destroy = nodeDestroy;
    nodeClass.debug = nodeDebug;
    DEBUG("  < getNode\n");
    return &nodeClass;
}
