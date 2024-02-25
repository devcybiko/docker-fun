#include "GMap.h"

static void debug(char * message)
{
    GMap *this = THIS(GMap_ID, "GMap.debug");
    printf("GMap.debug: %s\n", message);
    _(this->obj).debug("GMap.obj");
    _(this->list).debug("GMap.list");
}

static GEntry *getEntry(char * key)
{
    GMap *this = THIS(GMap_ID, "GMap.getEntry");
    GEntry *result = NULL;
    for (int i = 0; result == NULL && i < this->list->size; i++)
    {
        GEntry *entry = (GEntry *)_(this->list).get(i);
        if (entry->key == key)
            result = entry;
    }
    return result;
}

// void GMap::putEntries(GEntry entries[])
// {
//     for (int i = 0; !entries[i].key.empty(); i++)
//     {
//         GEntry entry = entries[i];
//         _(this).put(entry.key, entry.value);
//     }
// }

static void *get(char * key)
{
    GMap *this = THIS(GMap_ID, "GMap.get");
    GEntry *entry = _(this).getEntry(key);
    if (entry)
        return entry->value;
    return NULL;
}

static void put(char * key, void *value)
{
    GMap *this = THIS(GMap_ID, "GMap.put");
    GEntry *entry = _(this).getEntry(key);
    if (entry)
    {
        entry->value = value;
    }
    else
    {
        entry = (GEntry *) malloc(sizeof(GEntry));
        entry->key = key;
        entry->value = value;
        _(this->list).push(entry);
    }
}

static char TO_STRING_BUFF[100] = {};
static char *toString()
{
    GMap *this = THIS(GList_ID, "GMap.toString");
    sprintf(TO_STRING_BUFF, "GMap(%s): size=%d, extent=%d", this->obj->name, this->list->size, this->list->extent);
    return TO_STRING_BUFF;
}

static void delete()
{
    GMap *this = THIS(GMap_ID, "GMap.delete");
    _(this->obj).delete();
    _(this->list).delete();
    free(this);
}

GMap *GMap_new(char *name) {
    GMap *this = NEW(GMap);
    this->id = GMap_ID;
    this->obj = GObj_new(name);
    this->list = GList_new("gmap.list", 10, 1.5);

    this->debug = debug;
    this->delete = delete;
    this->toString = toString;

    this->put = put;
    this->getEntry = getEntry;
    this->debug = debug;
    this->get = get;

    return this;
}


