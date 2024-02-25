#include "GMap.h"

EXTENDS(GObj)

static void debug(char * message)
{
    GMap *this = THIS("GMap.debug");
    SUPER.debug(message);
    _(this->list).debug("GMap.list");
}

static GEntry *getEntry(char * key)
{
    GMap *this = THIS("GMap.getEntry");
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
    GMap *this = THIS("GMap.get");
    GEntry *entry = _(this).getEntry(key);
    if (entry)
        return entry->value;
    return NULL;
}

static void put(char * key, void *value)
{
    GMap *this = THIS("GMap.put");
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

static GMap *init(char *name)
{
    GMap *this = THIS("GMap.init");
    SUPER.init(name);
    this->put = put;
    this->getEntry = getEntry;
    this->debug = debug;
    this->get = get;

    this->list = GList_new("gmap.list", 10, 1.5);
    return this;
}

static void delete()
{
    GMap *this = THIS("GMap.delete");
    _(this->list).delete();
    free(this);
}

GMap *GMap_new(char *name) {
    INHERIT_FROM(GObj);
    GMap *this = NEW(GMap);
    this->init = init;
    return _(this).init(name);
}


