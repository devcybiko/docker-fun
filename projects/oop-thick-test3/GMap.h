#ifndef __GMap__
#define __GMap__

#include "GObj.h"
#include "GList.h"

typedef struct GEntry {
    char *key;
    void *value;
} GEntry;

#define GMap_CLASS \
    GList *list;

    ~GMap();
    void debug(std::string message);
    std::string toString();

    void put(std::string key, void *value);
    void *get(std::string key);
    GEntry *getEntry(std::string key);
    void putEntries(GEntry *entries);
};

GMap(std::string name); 

#endif // __GMap__
