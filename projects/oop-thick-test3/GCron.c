#include "GCron.h"
#include "GTimer.h"
#include "GCronEntry.h"

EXTENDS(GObj)

static void debug(char * message)
{
    GCron *this = THIS("GCron.debug");
    printf("DEBUG: %s\n", message);
    printf("DEBUG: this=%p\n", this);
    printf("DEBUG: list=%p\n", this->list);
    printf("DEBUG_super=%p\n", _super);
    SUPER.debug(message);
    _(this->list).debug(this->name);
}

static GCron *add(char * name, int msRepeat, int (*callback)(GCronEntry *), void *context)
{
    GCron *this = THIS("GCron.add");
    GCronEntry *entry = GCronEntry_new(name, msRepeat, callback, context);
    _(this).debug("pushing");
    _(this->list).push(entry);
    _(this->list).debug("adding... list");
    return this;
}

static int pump()
{
    GCron *this = THIS("GCron.pump");
    // returns the number of entries that were processed
    // if the number is 0, it means that no entries were processed
    int count = 0;
    int now = GTimer.mSecs();
    for (int i = 0; i < this->list->size; i++)
    {
        GCronEntry *entry = (GCronEntry *) _(this).list->get(i);
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

static void delete()
{
    GCron *this = THIS("GCron.delete");
    _(this).list->delete();
    SUPER.delete();
}

static GCron *init(char *name)
{
    GCron *this = THIS("GCron.init");
    SUPER.init(name);
    this->delete = delete;
    this->debug = debug;
    this->add = add;
    this->pump = pump;

    this->list = GList_new("GCron.list", 0, 0.0);
    return this;
}

GCron *GCron_new(char * name) {
    INHERIT_FROM(GObj);
    GCron *this = NEW(GCron);
    this->init = init;
    return _(this).init(name);
}
