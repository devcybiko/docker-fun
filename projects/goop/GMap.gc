#define TRACE_OFF

#include "GMap.h"

GMap* GMap_new() {
    if (GMap$.id == 0) _initClass();
    GMap* this = NEW(GMap);
    this->class = &GMap$;
    _(this).init(GMap_ID);
    return this;
}

static void init(GID id) {
    GMap* this = THIS(GMap, "GMap.init");
    __(this).init(id);
    this->list = GList_new_full(8, 2);
}

static void debug(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    GMap* this = THIS(GMap, "GMap.debug");
    __(this).debug(fmt, args);
}

static void delete() {
    GMap* this = THIS(GMap, "GMap.delete");
    _(this->list).delete();
    __(this).delete();
}

static GEntry* getEntry(char* key) {
    GMap* this = THIS(GMap, "GMap.getEntry");
    GEntry* result = NULL;
    for (int i = 0; result == NULL && i < this->list->size; i++) {
        GEntry* entry = (GEntry*)_(this->list).get(i);
        if (strcmp(entry->key, key) == 0) 
            result = entry;
    }
    return result;
}

static void putEntries(GEntry* entries) {
    GMap* this = THIS(GMap, "GMap.putEntries");
    for (int i = 0; entries[i].key; i++) {
        GEntry entry = entries[i];
        _(this).put(entry.key, entry.value);
    }
}

static void* get(char* key) {
    GMap* this = THIS(GMap, "GMap.get");
    GEntry* entry = _(this).getEntry(key);
    void *result = NULL;
    if (entry) result = entry->value;
    return result;
}

static void put(char* key, void* value) {
    GMap* this = THIS(GMap, "GMap.put");
    GEntry* entry = _(this).getEntry(key);
    if (entry) {
        entry->value = value;
    } else {
        entry = NEW(GEntry);
            entry->key = key;
            entry->value = value;
                (_THIS_=this->list, *(this->list->class)).push(entry);
        // _(this->list).push(entry);
    }
}

GMapClass GMap$;
static void _initClass() {
    memcpy(&GMap$, &GObj$, sizeof(GObj$));
    GMap$.name = "GMap";
    GMap$.id = GMap_ID;
    GMap$.super = &GObj$;
    GMap$.init = init;
    GMap$.delete = delete;
    GMap$.debug = debug;
    GMap$.get = get;
    GMap$.put = put;
    GMap$.getEntry = getEntry;
    GMap$.putEntries = putEntries;
}
