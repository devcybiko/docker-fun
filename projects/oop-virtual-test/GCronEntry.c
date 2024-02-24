#include "GCronEntry.h"
#include "GTimer.h"

static GCronEntry *new(char *name, int msRepeat, int (*callback)(GCronEntry *), void *context)
{
    DEBUG("> GCronEntry.new %s\n", name);
    GCronEntry *this = NEW(GCronEntry);
    this->class = GCronEntry$;
    this->super = GCronEntrySuper$;
    _(this)->init(name, msRepeat, callback, context);
    DEBUG("< GCronEntry.new %s\n", name);
    return this;
}

static GCronEntry *init(char *name, int msRepeat, int(*callback(GCronEntry *)), void *context)
{
    GCronEntry *this = THIS;
    DEBUG("> GCronEntry.init %s\n", name);
    __(this)->init(name);
    this->msRepeat = msRepeat;
    this->msLast = GTimer.mSecs();
    this->callback = callback;
    this->context = context;
    DEBUG("< GCronEntry.init %s\n", name);
    return _(this);
}

static void delete()
{
    GCronEntry *this = THIS;
    DEBUG("> GCronEntry.delete %s\n", this->name);
    __(this)->delete();
    free(this);
    DEBUG("< GCronEntry.delete %s\n", this->name);
}

static GCronEntryClass *debug(char *args)
{
    GCronEntry *this = THIS;
    DEBUG("> GCronEntry.debug %s\n", this->name);
    __(this)->debug(args);
    DEBUG("< GCronEntry.debug %s\n", this->name);
    return _(this);
}

START_LINKAGES(GCronEntry, GObj)
LINKAGE(new)
LINKAGE(init)
LINKAGE(delete)
LINKAGE(debug)
END_LINKAGES(GCronEntry, GObj)
