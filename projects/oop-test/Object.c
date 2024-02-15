#include "Object.h"

static Object *objectInit(Object *this, char *name) {
    DEBUG("  > objectInit\n");
    this->name = strdup(name);
    DEBUG("  < objectInit\n");
    return this;
}

static Object *objectDebug(Object *this, char *args) {
    printf("name: %s - %s\n", this->name, args);
    return this;
}

static void objectDestroy(Object *this) {
    DEBUG("  > objectDestroy %s\n", this->name);
    free(this->name);
    free(this);
    DEBUG("  < objectDestroy\n");
}

Object *objectNew(char *name) {
    DEBUG("  > objectNew\n");
    Object *obj = NEW(Object);
    obj->init = objectInit;
    obj->destroy = objectDestroy;
    obj->debug = objectDebug;
    obj->init(obj, name);
    DEBUG("  < objectNew\n");
    return obj;
}
