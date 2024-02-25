#include "GObj.h"

void *_THIS; // this

static void delete()
{
    GObj *this = THIS(GObj_ID, "Gobj.delete");
    free(this);
}

static char *toString()
{
    GObj *this = THIS(GObj_ID, "GObj.toString");
    return this->name;
}

static void debug(char *message)
{
    GObj *this = THIS(GObj_ID, "GObj.debug");
    printf("%s says \"%s\"\n", this->name, message);
}

GObj *GObj_new(char *name) {
    GObj *this = NEW(GObj);
    printf(">>> GObj.new %s\n", name);
    strncpy(this->name, name, sizeof(this->name) - 1);
    this->id = GObj_ID;
    this->name[sizeof(this->name) - 1] = '\0'; // strncpy does not null terminate
    this->delete = delete;
    this->debug = debug;
    this->toString = toString;
    return this;
}

void *_this(int obj_id, char *name)
{
    void *this = _THIS;
    if (this == NULL)
    {
        printf("ERROR: \"%s\" called with \"->\" instead of \"_(x).\" \n", name);
        exit(1);
    }
    int id = ((GObj *)this)->id;
    if (id != obj_id)
    {
        printf("ERROR: \"%s\" called with wrong object type (expected %x, got %x)\n", name, obj_id, id);
        exit(1);
    }
    _THIS = NULL;
    return this;
}
