#include "GCron.h"
#include "GTimer.h"
#include "GCronEntry.h"

GCron::GCron(std::string name) : GObj(name)
{
    this->list = new GList("list", 10, 2);
    this->list->debug("list");
}

GCron::~GCron()
{
    delete this->list;
}

void GCron::debug(std::string args)
{
    GObj::debug(args);
    this->list->debug("list");
}

GCron *GCron::add(std::string name, int msRepeat, int (*callback)(GCronEntry *), void *context)
{
    GCronEntry *entry = new GCronEntry(name, msRepeat, callback, context);
    this->list->push(entry);
    return this;
}

int GCron::pump()
{
    // returns the number of entries that were processed
    // if the number is 0, it means that no entries were processed
    int count = 0;
    int now = GTimer.mSecs();
    for (int i = 0; i < this->list->size; i++)
    {
        GCronEntry *entry = (GCronEntry *) this->list->get(i);
        if (entry && !(entry->flags & GCRON_DEACTIVATED))
        {
            count++;
            if (entry->msLast + entry->msRepeat < now)
            {
                int newFlags = entry->callback(entry);
                entry->flags = newFlags;
                entry->msLast = now;
            }
        }
    }
    return count;
}
