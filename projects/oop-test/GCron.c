#include "GCron.h"
#include "GTimer.h"

extern GCronClass *GCron$;

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

static void destroy()
{
    GCron *this = THIS;
    DEBUG("> GCron.destroy %s\n", this->name);
    _(this->list)->destroy();
    __(this)->destroy();
    free(this);
    DEBUG("< GCron.destroy %s\n", this->name);
}

static GCronClass *debug(char *args)
{
    GCron *this = THIS;
    DEBUG("> GCron.debug %s\n", this->name);
    __(this)->debug(args);
    DEBUG("< GCron.debug %s\n", this->name);
    return _(this);
}

static GCronEntry *newEntry(char *name, int msRepeat, GFunc callback, void *context)
{
    DEBUG("> GCron.newEntry %s\n", name);
    GCronEntry *entry = NEW(GCronEntry);
    entry->class = GObj$;
    entry->super = GObj$;
    __(entry)->init(name);
    entry->msRepeat = msRepeat;
    entry->msLast = GTIMER->mSecs();
    entry->callback = callback;
    entry->context = context;
    DEBUG("< GCron.newEntry %s\n", name);
    return entry;
}

static GCronClass *add(char *name, int msRepeat, int (*callback)(struct GCronEntry *), void *context)
{
    GCron *this = THIS;
    DEBUG("> GCron.add %s\n", name);
    GCronEntry *entry = newEntry(name, msRepeat, callback, context);
    THIS=this->list;
    printf("63, %p\n", this->list);
    THIS=this;
    _(this->list)->push(entry);
    DEBUG("< GCron.add %s\n", name);
    return _(this);
}

static GCronClass *pump()
{
    GCron *this = THIS;
    DEBUG("> GCron.pump %s\n", this->name);
    int now = GTIMER->mSecs(); // get current time in mSecs
    for (int i = 0; i < this->list->size; i++)
    {
        GCronEntry *entry = (GCronEntry *) _(this->list)->get(i);
        if (entry && !(entry->flags & GCRON_DEACTIVATED))
        {
            // DEBUG("now=%d, msLast=%d, msRepeat=%d, %d\n", now, entry->msLast, entry->msRepeat, entry->msLast + entry->msRepeat < now);
            if (entry->msLast + entry->msRepeat < now)
            {
                int newFlags = entry->callback(entry);
                entry->flags = newFlags;
                entry->msLast = now;
            }
        }
    }
    DEBUG("< GCron.pump %s\n", this->name);
    return _(this);
}

const GCronClass _GCron$ = {
    .new = new,
    .init = init,
    .destroy = destroy,
    .debug = debug,
    .pump = pump,
    .add = add,
};

GCronClass *GCron$ = &_GCron$;
GObjClass *GCronSuper$ = &_GObj$;