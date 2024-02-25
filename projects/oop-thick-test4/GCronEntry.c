#include "GCronEntry.h"
#include "GTimer.h"

EXTENDS(GObj)

static void debug(char * message)
{
    GCronEntry *this = THIS("GCronEntry.debug");
    SUPER.debug(message);
    printf("msRepeat: %d\n", _(this).msRepeat);
    printf("msLast: %d\n", _(this).msLast);
    printf("flags: %d\n", _(this).flags);
    printf("context: %d\n", _(this).context);
}

static GCronEntry *init(char * name, int msRepeat, int (*callback)(GCronEntry *self), void *context) {
    GCronEntry *this = THIS("GCronEntry.init");
    SUPER.init(name);
    this->debug = debug;
    
    this->msRepeat = msRepeat;
    this->msLast = GTimer.mSecs();
    this->callback = callback;
    this->context = context;
    return this;
}

GCronEntry *GCronEntry_new(char * name, int msRepeat, int (*callback)(GCronEntry *self), void *context) {
    INHERIT_FROM(GObj);
    GCronEntry *this = NEW(GCronEntry);
    this->init = init;
    return _(this).init(name, msRepeat, callback, context);
}

