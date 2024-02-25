#include "GCronEntry.h"
#include "GTimer.h"

static void delete()
{
    GCronEntry *this = THIS(GCronEntry_ID, "GCronEntry.delete");
    free(this);
}

static char *toString()
{
    GCronEntry *this = THIS(GCronEntry_ID, "GCronEntry.toString");
    sprintf(GObj_stringbuffer, "GCronEntry(%s): msRepeat=%d, msLast=%d", this->name, this->msRepeat, this->msLast);
    return GObj_stringbuffer;
}

static void debug(char * message)
{
    GCronEntry *this = THIS(GCronEntry_ID, "GCronEntry.debug");
    printf("msRepeat: %d\n", _(this).msRepeat);
    printf("msLast: %d\n", _(this).msLast);
    printf("flags: %d\n", _(this).flags);
    printf("context: %p\n", _(this).context);
}

GCronEntry *GCronEntry_new_full(char * name, int msRepeat, int (*callback)(GCronEntry *self), void *context) {
    GCronEntry *this = NEW(GCronEntry);
    GObj_init(this, name, GCronEntry_ID);
    this->msRepeat = msRepeat;
    this->msLast = GTimer.mSecs();
    this->callback = callback;
    this->context = context;
    
    this->debug = debug;
    this->delete = delete;
    this->toString = toString;

    return this;
}

GCronEntry *GCronEntry_new(int msRepeat, int (*callback)(GCronEntry *self), void *context) {
    return GCronEntry_new_full("GCronEntry", msRepeat, callback, context);
}