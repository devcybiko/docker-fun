#include "GMap.h"
#include "GString.h"

#define DEBUG // printf

static void debug(char *message)
{
    GMap *this = THIS(GMap_ID, "GMap.debug");
    DEBUG("GMap.debug: %s says \"%s\"\n", this->name, message);
    _(this->keys).debug("GMap.keys");
}

static int _find(GMap *this, char *theKey)
{
    int result = -1;
    for (int i = 0; i < this->keys->size; i++)
    {
        DEBUG("GMap._find: %d\n", i);
        GString *key = _(this->keys).get(i);
        DEBUG("GMap._find: %p\n", key);
        if (key && _(key).equals(theKey))
        {
            DEBUG("GMap._find: %s found at %d\n", theKey, i);
            return i;
        }
    }
    return -1;
}

static GObj *get(char *theKey)
{
    GMap *this = THIS(GMap_ID, "GMap.get");
    int index = _find(this, theKey);
    if (index == -1)
        return NULL;
    return _(this->values).get(index);
}

static void put(char *theKey, void *theValue)
{
    GMap *this = THIS(GMap_ID, "GMap.put");
    DEBUG("> GMap.put: %s=%p\n", theKey, theValue);
    int index = _find(this, theKey);
    if (index == -1)
    {
        GString *key = GString_new(theKey);
        DEBUG("GMap.put: %s not found, adding %p\n", theKey, key);
        _(this->keys).push(key);
        _(this->values).push(theValue);
    }
    else
    {
        _(this->values).set(index, theValue);
    }
    DEBUG("< GMap.put: %s=%p\n", theKey, theValue);
}

static char *toString()
{
    GMap *this = THIS(GList_ID, "GMap.toString");
    sprintf(GObj_stringbuffer, "GMap(%s): size=%d, extent=%d", this->name, this->keys->size, this->keys->extent);
    return GObj_stringbuffer;
}

static void delete()
{
    GMap *this = THIS(GMap_ID, "GMap.delete");
    _(this->keys).delete();
    _(this->values).safeDelete(); // don't free the objects, just the array
    free(this);
}

GMap *GMap_new_full(char *name)
{
    GMap *this = NEW(GMap);
    GObj_init(this, name, GMap_ID);
    this->keys = GList_new_full("gmap.keys", 10, 1.5);
    this->values = GList_new_full("gmap.values", 10, 1.5);
    this->values->safe = true; // don't free the objects, just the array

    this->debug = debug;
    this->delete = delete;
    this->toString = toString;

    this->put = put;
    this->get = get;

    return this;
}

GMap *GMap_new()
{
    return GMap_new_full("GMap");
}