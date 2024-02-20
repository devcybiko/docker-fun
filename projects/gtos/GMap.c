#include "GMap.h"

static GMapClass *debug(GMap *this, char *args)
{
    DEBUG("  > debug\n");
    GOBJ->debug((GObj *) this, args);
    DEBUG(" < debug\n");
    return GMAP;
}

static void destroy(GMap *this)
{
    DEBUG("    > destroy\n");
    GOBJ->destroy((GObj *) this);
    free(this);
    DEBUG("    < destroy\n");
}

static GMapClass *init(GMap *this, char *name)
{
    DEBUG("    > init\n");
    GOBJ->init((GObj *) this, name);
    DEBUG("    < init\n");
    return GMAP;
}

static GMap *new(char *name)
{
    DEBUG("  > new\n");
    GMap *this = NEW(GMap);
    this->list = GLIST->new("list", 8, 2);
    GMAP->init(this, name);
    DEBUG("  < new\n");
    return this;
}

static GEntry *find(GMap *this, char *key)
{
    DEBUG("    > entry\n");
    for(int i=0; i<this->list->size; i++) {
        GEntry *entry = (GEntry *)GLIST->get(this->list, i);
        if (strcmp(entry->key, key) == 0) return entry;
    }
    DEBUG("    < entry\n");
    return NULL;
}

static GEntry *addMap(GMap *this, GEntry *entries)
{
    DEBUG("    > addMap\n");
    for(int i=0; entries[i].key; i++) {
    printf("52 %s\n", entries[i].key);
        GEntry entry = entries[i];
        GMAP->put(this, entry.key, entry.value);
    }
    DEBUG("    < entry\n");
    return NULL;
}

static void *get(GMap *this, char *key)
{
    DEBUG("    > get\n");
    GEntry *entry = GMAP->find(this, key);
    if (entry) return entry->value;
    DEBUG("    < get\n");
    return NULL;
}

static GEntry *put(GMap *this, char *key, void *value)
{
    DEBUG("    > put\n");
    GEntry *entry = GMAP->find(this, key);
    if (entry) {
        entry->value = value;
    } else {
        entry = NEW(GEntry);
        entry->key = key;
        entry->value = value;
        GLIST->push(this->list, entry);
    }
    DEBUG("    < put\n");
    return entry;
}

static GMapClass _GMAP = {
    .new = new,
    .init = init,
    .destroy = destroy,
    .debug = debug,
    .put = put,
    .get = get,
    .find = find,
    .addMap = addMap,
};

GMapClass *GMAP = &_GMAP;