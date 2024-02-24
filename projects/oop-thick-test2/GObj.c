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

GObj *GObj_init(GObj *this, char *name)
{
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->delete = delete;
    this->debug = debug;
    this->toString = toString;
    return this;
}

GObj *GObj_new(char *name) {
    GObj *this = NEW(GObj);
    return GObj_init(this, name);
}
