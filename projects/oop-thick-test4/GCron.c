#include "GCron.h"
#include "GTimer.h"
#include "GCronEntry.h"

static void debug(char *message)
{
    GCron *this = THIS(GCron_ID, "GCron.debug");
    printf("GCron: %s\n", message);
    _(this->obj).debug("Gcron.obj");
    _(this->list).debug("GCron.list");
}

static GCron *add(char *name, int msRepeat, int (*callback)(GCronEntry *), void *context)
{
    GCron *this = THIS(GCron_ID, "GCron.add");
    GCronEntry *entry = GCronEntry_new(name, msRepeat, callback, context);
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

static char TO_STRING_BUFF[100] = {};
static char *toString()
{
    GCron *this = THIS(GCron_ID, "GCron.toString");
    sprintf(TO_STRING_BUFF, "GCron(%s)", this->obj->name);
    return TO_STRING_BUFF;
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
    _(this->obj).delete();
    free(this);
}

GCron *GCron_new(char *name)
{
    GCron *this = NEW(GCron);
    this->id = GCron_ID;
    this->obj = GObj_new(name);
    this->list = GList_new("GCron.list", 0, 0.0);

    this->delete = delete;
    this->debug = debug;
    this->toString = toString;

    this->add = add;
    this->pump = pump;
    return this;
}
