#include "GMap.h"

GMap::GMap(std::string name) : GObj(name)
{
    this->list = new GList("list", 8, 2);
}

GMap::~GMap()
{
    // destroy this->list;
    delete this->list;
}

void GMap::debug(std::string message)
{
    GObj::debug(message);
    this->list->debug("");
}

GEntry *GMap::getEntry(std::string key)
{
    GEntry *result = NULL;
    for (int i = 0; result == NULL && i < this->list->size; i++)
    {
        GEntry *entry = (GEntry *)this->list->get(i);
        if (entry->key == key)
            result = entry;
    }
    return result;
}

void GMap::putEntries(GEntry entries[])
{
    for (int i = 0; !entries[i].key.empty(); i++)
    {
        GEntry entry = entries[i];
        this->put(entry.key, entry.value);
    }
}

void *GMap::get(std::string key)
{
    GEntry *entry = this->getEntry(key);
    if (entry)
        return entry->value;
    return NULL;
}

void GMap::put(std::string key, void *value)
{
    GEntry *entry = this->getEntry(key);
    if (entry)
    {
        entry->value = value;
    }
    else
    {
        entry = (GEntry *) malloc(sizeof(GEntry));
        entry->key = key;
        entry->value = value;
        this->list->push(entry);
    }
}