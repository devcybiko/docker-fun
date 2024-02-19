#include "Object.h"

static ObjectClass objectClass;

static ObjectClass *objectInit(Object *this, char *name) {
    DEBUG("  > objectInit\n");
    this->name = strdup(name);
    DEBUG("  < objectInit\n");
    return &objectClass;
}

static ObjectClass *objectDebug(Object *this, char *args) {
    printf("name: %s - %s\n", this->name, args);
    return &objectClass;
}

static ObjectClass *objectDestroy(Object *this) {
    DEBUG("  > objectDestroy %s\n", this->name);
    free(this->name);
    free(this);
    DEBUG("  < objectDestroy\n");
    return &objectClass;
}

static Object *objectNew(char *name) {
    DEBUG("  > objectNew\n");
    Object *this = NEW(Object);
    objectClass.init(this, name);
    DEBUG("  < objectNew\n");
    return this;
}

ObjectClass *getObjectClass()
{
    DEBUG("  > getObjectClass\n");
    objectClass.new = objectNew;
    objectClass.init = objectInit;
    objectClass.destroy = objectDestroy;
    objectClass.debug = objectDebug;
    DEBUG("  < getObjectClass\n");
    return &objectClass;
}
