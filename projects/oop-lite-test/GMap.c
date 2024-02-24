#include "GMap.h"

static GMap *new(char *name)
{
    DEBUG("> GMap.new %s\n", name);
    GMap *this = NEW(GMap);
    this->class = GMap$;
    this->super = GObj$;
    _(this)->init(name);
    DEBUG("< GMap.new %s\n", name);
    return this;
}

static GMapClass *init(char *name)
{
    GMap *this = THIS;
    DEBUG("> GMap.init %s\n", name);
    __(this)->init(name);
    this->list = GList$->new ("list", 8, 2);
    DEBUG("< GMap.init %s\n", name);
    return _(this);
}

static GMapClass *debug(char *args)
{
    GMap *this = THIS;
    DEBUG("> GMap.debug %s\n", this->name);
    __(this)->debug(args);
    DEBUG("< GMap.debug %s\n", this->name);
    return _(this);
}

static void destroy()
{
    GMap *this = THIS;
    DEBUG("> GMap.destroy %s\n", this->name);
    __(this)->destroy();
    _(this->list)->destroy();
    free(this);
    DEBUG("< GMap.destroy\n");
}

static GEntry *getEntry(char *key)
{
    GMap *this = THIS;
    DEBUG("> GMap.getEntry %s\n", key);
    GEntry *result = NULL;
    for (int i = 0; result == NULL && i < this->list->size; i++)
    {
        GEntry *entry = (GEntry *)_(this->list)->get(i);
        if (strcmp(entry->key, key) == 0)
            result = entry;
    }
    DEBUG("< GMap.getEntry %s\n", key);
    return result;
}

static GMapClass *putEntries(GEntry *entries)
{
    GMap *this = THIS;
    DEBUG("> GMap.putEntries\n");
    for (int i = 0; entries[i].key; i++)
    {
        GEntry entry = entries[i];
        _(this)->put(entry.key, entry.value);
    }
    DEBUG("< GMap.putEntries\n");
    return _(this);
}

static void *get(char *key)
{
    GMap *this = THIS;
    DEBUG("< GMap.get %s\n", key);
    GEntry *entry = _(this)->getEntry(key);
    if (entry)
        return entry->value;
    DEBUG("< GMap.getEntry %s\n", key);
    return NULL;
}

static GEntry *put(char *key, void *value)
{
    GMap *this = THIS;
    DEBUG("> GMap.put %s\n", key);
    GEntry *entry = _(this)->getEntry(key);
    if (entry)
    {
        entry->value = value;
    }
    else
    {
        entry = NEW(GEntry);
        entry->key = key;
        entry->value = value;
        _(this->list)->push(entry);
    }
    DEBUG("< GMap.put %s\n", key);
    return entry;
}

const GMapClass _GMap$ = {
    .new = new,
    .init = init,
    .destroy = destroy,
    .debug = debug,
    .put = put,
    .get = get,
    .getEntry = getEntry,
    .putEntries = putEntries,
};

GMapClass *GMap$ = &_GMap$;
GObjClass *GMapSuper$ = &_GObj$;