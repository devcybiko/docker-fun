#ifndef __GMap__
#define __GMap__

#include "GObj.h"
#include "GList.h"

typedef struct GEntry {
    std::string key;
    void *value;
} GEntry;

class GMap : public GObj
{
public:
    GList *list;

    GMap(std::string name); 
    ~GMap();
    void debug(std::string message);
    std::string toString();

    void put(std::string key, void *value);
    void *get(std::string key);
    GEntry *getEntry(std::string key);
    void putEntries(GEntry *entries);
};

#endif // __GMap__
