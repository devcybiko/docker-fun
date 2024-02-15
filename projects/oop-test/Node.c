#include "Node.h"

static void initNode(void *_this, char *name, Node *parent) {
    Node *this = _this;
    DEBUG("    > initNode\n");
    _NodeClass.super->init(this, name);
    this->_ = &_NodeClass;
    this->parent = parent;
    DEBUG("    < initNode\n");
}

static void debug(void *_this, char *args) {
    Node *this = _this;
    this->_->super->debug(this, args);
    printf("Node.parent: %p\n", this->parent);
    printf("Node.children: %p\n", this->children);
}

static void initNodeClass(void *_thisClass) {
    NodeClass *thisClass = _thisClass;
    _NodeParent->initClass(thisClass);
    thisClass->super = _NodeParent;
    thisClass->initClass = initNodeClass;
    thisClass->initNode = initNode;
    thisClass->debug = (void *) debug;
}

Node *newNode(char *name, Node *parent) {
    DEBUG("  > newNode\n");
    if (!_NodeClass.initNode) initNodeClass(&_NodeClass);
    Node *this = NEW(Node);
    _NodeClass.initNode(this, name, parent);
    DEBUG("  < newNode\n");
    return this;
}