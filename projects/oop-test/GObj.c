#include "GObj.h"

void *THIS; // this

static GObj *new(char *name) {
    DEBUG("  > GObjNew\n");
    GObj *this = NEW(GObj);
    this->class = GObj$;
    this->super = NULL; // there are no super classes for OBJ
    _(this)->init(name);
    DEBUG("  < GObjNew\n");
    return THIS=this;
}

static GObjClass *init(char *name) {
    GObj *this = THIS;
    DEBUG("  > GObjInit %s\n", name);
    strncpy(this->name, name, sizeof(this->name) - 1);
    DEBUG("  < GObjInit %s\n", name);
    return _(this);
}

static void destroy() {
    GObj *this = THIS;
    DEBUG("  > GObjDestroy %s\n", this->name);
    // nothing to do here
    DEBUG("  < GObjDestroy\n");
}

static GObjClass *debug(char *args) {
    GObj *this = THIS;
    printf("name: %s - %s\n", this->name, args);
    return _(this);
}

const GObjClass _GObj$ = {
    .new = new,
    .init = init,
    .destroy = destroy,
    .debug = debug,
};

const GObjClass *GObj$ = &_GObj$;
