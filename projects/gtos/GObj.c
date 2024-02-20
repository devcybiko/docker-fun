#include "GObj.h"

static GObjClass *init(GObj *this, char *name) {
    DEBUG("  > GObjInit\n");
    strncpy(this->name, name, sizeof(this->name) - 1);
    DEBUG("  < GObjInit\n");
    return GOBJ;
}

static GObjClass *debug(GObj *this, char *args) {
    printf("name: %s - %s\n", this->name, args);
    return GOBJ;
}

static GObjClass *destroy(GObj *this) {
    DEBUG("  > GObjDestroy %s\n", this->name);
    DEBUG("  < GObjDestroy\n");
    return GOBJ;
}

static GObj *new(char *name) {
    DEBUG("  > GObjNew\n");
    GObj *this = NEW(GObj);
    GOBJ->init(this, name);
    DEBUG("  < GObjNew\n");
    return this;
}

static GObjClass _GOBJ = {
    .new = new,
    .init = init,
    .destroy = destroy,
    .debug = debug,
};

GObjClass *GOBJ = &_GOBJ;