#include "GString.h"

#define DEBUG // DEBUG

static char *set(char *value)
{
    GString *this = THIS(GString_ID, "GString.set");
    free(this->value);
    this->value = strdup(value);
    return this->value;
}

static void get()
{
    GString *this = THIS(GString_ID, "GString.get");
    return this->value;
}

static void debug(char *message)
{
    GString *this = THIS(GString_ID, "GString.debug");
    DEBUG("GString: %s=%s\n", this->name, this->value);
}

static void delete()
{
    GString *this = THIS(GString_ID, "GString.delete");
    free(this->value);
    free(this);
}

static int equals(char *that)
{
    GString *this = THIS(GString_ID, "GString.equals");
    DEBUG("GString.equals: %s %s %s\n", this->name, this->value, that);
    int result = strcmp(this->value, that) == 0;
    DEBUG("GString.equals: %s %s %s %d\n", this->name, this->value, that, result);
    return result;
}

static char *toString()
{
    GString *this = THIS(GString_ID, "GString.toString");
    return this->value;
}

GString *GString_new_full(char *name, char *value)
{
    GString *this = NEW(GString);
    DEBUG("GString.new ...%p name: %s value: %s\n", this, name, value);
    GObj_init(this, name, GString_ID);

    this->value = strdup(value);
    this->delete = delete;
    this->toString = toString;
    this->debug = debug;

    this->set = set;
    this->get = get;
    this->equals = equals;
    return this;
}

GString *GString_new(char *value)
{
    return GString_new_full("GString", value);
}