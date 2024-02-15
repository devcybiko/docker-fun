#include "Object.h"

static ObjectClass objectClass;

static ObjectInstance *objectNew(char *name) {
    DEBUG("  > objectNew\n");
    ObjectInstance *obj = NEW(ObjectInstance);
    objectClass.init(obj, name);
    DEBUG("  < objectNew\n");
    return obj;
}

static void objectInit(void *_this, char *name) {
    ObjectInstance *this = _this;
    DEBUG("  > objectInit\n");
    this->name = strdup(name);
    DEBUG("  < objectInit\n");
}

static void debug(void *_this, char *args) {
    ObjectInstance *this = (ObjectInstance *)_this;
    printf("name: %s - %s\n", this->name, args);
}

static void objectDestroy(void *_this) {
    ObjectInstance *this = _this;
    DEBUG("  > objectDestroy %s\n", this->name);
    free(this->name);
    free(this);
    DEBUG("  < objectDestroy\n");
}


ObjectClass *getObjectClass() {
    objectClass.super = NULL;
    objectClass.new = objectNew;
    objectClass.init = objectInit;
    objectClass.destroy = objectDestroy;
    objectClass.debug = debug;
    return &objectClass;
}

