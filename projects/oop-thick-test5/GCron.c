#include "GCron.h"
#include "GTimer.h"
#include "GCronEntry.h"

static void debug(char *message)
{
    GCron *this = THIS(GCron_ID, "GCron.debug");
    printf("GCron(%s): %s\n", this->name, message);
    _(this->list).debug("GCron.list");
}

static GCron *add(char *name, int msRepeat, int (*callback)(GCronEntry *), void *context)
{
    GCron *this = THIS(GCron_ID, "GCron.add");
    GCronEntry *entry = GCronEntry_new(msRepeat, callback, context);
    _(this).debug("pushing");
    _(this->list).push(entry);
    _(this->list).debug("adding... list");
    return this;
}

static int pump()
{
    GCron *this = THIS(GCron_ID, "GCron.pump");
    // returns the number of entries that were processed
    // if the number is 0, it means that no entries were processed
    int count = 0;
    int now = GTimer.mSecs();
    for (int i = 0; i < this->list->size; i++)
    {
        GCronEntry *entry = (GCronEntry *)_(this->list).get(i);
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

static char *toString()
{
    GCron *this = THIS(GCron_ID, "GCron.toString");
    sprintf(GObj_stringbuffer, "GCron(%s)", this->name);
    return GObj_stringbuffer;
}

static void delete()
{
    GCron *this = THIS(GCron_ID, "GCron.delete");
    for (int i = 0; i < this->list->size; i++)
    {
        GCronEntry *entry = (GCronEntry *)_(this->list).get(i);
        _(entry).delete();
    }
    _(this->list).delete();
    free(this);
}

GCron *GCron_new(char *name)
{
    GCron *this = NEW(GCron);
    GObj_init(this, name, GCron_ID);
    this->list = GList_new("GCron.list", 0, 0.0);

    this->delete = delete;
    this->debug = debug;
    this->toString = toString;

    this->add = add;
    this->pump = pump;
    return this;
}
