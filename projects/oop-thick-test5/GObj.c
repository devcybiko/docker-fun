#include "GObj.h"

void *_THIS_; // this

char GObj_stringbuffer[256] = {};

void GObj_delete()
{
    GObj *this = THIS(GObj_ID, "Gobj.delete");
    free(this);
}

char *GObj_toString()
{
    GObj *this = _THIS(GObj_ID, "GObj.toString");
    return this->name;
}

void GObj_debug(char *message)
{
    GObj *this = _THIS(GObj_ID, "GObj.debug");
    printf("%s says \"%s\"\n", this->name, message);
}

GObj *GObj_init(GObj *this, char *name, int id)
{
    this->id = id;
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0'; // strncpy does not null terminate
    this->delete = GObj_delete;
    this->debug = GObj_debug;
    this->toString = GObj_toString;
    return this;
}

GObj *GObj_new(char *name) {
    GObj *this = NEW(GObj);
    printf(">>> GObj.new %s\n", name);
    return GObj_init(this, name, GObj_ID);
}
