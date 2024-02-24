#include "GObj.h"

void *THIS; // this

static void delete()
{
    GObj *this = THIS;
    free(this);
}

static char *toString()
{
    GObj *this = THIS;
    return this->name;
}

static void debug(char *message)
{
    GObj *this = THIS;
    printf("GObj: %s: %s\n", this->name, message);
}

static GObj *init(char *name)
{
    GObj *this = THIS;
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->delete = delete;
    this->debug = debug;
    this->toString = toString;
    return this;
}

GObj *GObj_new(char *name) {
    GObj *this = NEW(GObj);
    this->init = init;
    return _(this)->init(name);
}
