#include "GCron.h"
#include "GTimer.h"
#include "GCronEntry.h"

static GCron *new(char *name)
{
    DEBUG("> GCron.new %s\n", name);
    GCron *this = NEW(GCron);
    this->class = GCron$;
    this->super = GCronSuper$;
    _(this)->init(name);
    DEBUG("< GCron.new %s\n", name);
    return this;
}

static GCron *init(char *name)
{
    GCron *this = THIS;
    DEBUG("> GCron.init %s\n", name);
    __(this)->init(name);
    this->list = GList$->new ("cron.list", 8, 2);
    DEBUG("< GCron.init %s\n", name);
    return _(this);
}

static void delete()
{
    GCron *this = THIS;
    DEBUG("> GCron.delete %s\n", this->name);
    _(this->list)->delete();
    __(this)->delete();
    free(this);
    DEBUG("< GCron.delete %s\n", this->name);
}

static GCronClass *debug(char *args)
{
    GCron *this = THIS;
    DEBUG("> GCron.debug %s\n", this->name);
    __(this)->debug(args);
    DEBUG("< GCron.debug %s\n", this->name);
    return _(this);
}

static GCronClass *add(char *name, int msRepeat, int (*callback)(struct GCronEntry *), void *context)
{
    GCron *this = THIS;
    DEBUG("> GCron.add %s\n", name);
    GCronEntry *entry = GCronEntry$->new(name, msRepeat, callback, context);
    _(this->list)->push(entry);
    DEBUG("< GCron.add %s\n", name);
    return _(this);
}

static int pump()
{
    GCron *this = THIS;
    // returns the number of entries that were processed
    // if the number is 0, it means that no entries were processed
    int count = 0;
    int now = GTimer.mSecs();
    for (int i = 0; i < this->list->size; i++)
    {
        GCronEntry *entry = (GCronEntry *) _(this->list)->get(i);
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

const GCronClass _GCron$ = {
    .new = new,
    .init = init,
    .delete = delete,
    .debug = debug,
    .pump = pump,
    .add = add,
};

GCronClass *GCron$ = &_GCron$;
GObjClass *GCronSuper$ = &_GObj$;