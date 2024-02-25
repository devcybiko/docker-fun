#include "GObj.h"

void *_THIS; // this

static void delete()
{
    GObj *this = THIS("Gobj.delete");
    free(this);
}

static char *toString()
{
    GObj *this = THIS("GObj.toString");
    return this->name;
}

static void debug(char *message)
{
    GObj *this = THIS("GObj.debug");
    printf("%s says \"%s\"\n", this->name, message);
}

static GObj *init(char *name)
{
    GObj *this = THIS("GObj.init");
    printf(">>> GObj.init %s\n", name);
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0'; // strncpy does not null terminate
    this->delete = delete;
    this->debug = debug;
    this->toString = toString;
    return this;
}

GObj *GObj_new(char *name) {
    GObj *this = NEW(GObj);
    this->init = init;
    return _(this).init(name);
}

void *_this(char *name)
{
    void *this = _THIS;
    if (this == NULL)
    {
        printf("ERROR: \"%s\" called with \"->\" instead of \"_(x).\" \n", name);
        exit(1);
    }
    _THIS = NULL;
    return this;
}
