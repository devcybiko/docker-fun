#include "GCronEntry.h"
#include "GTimer.h"

static void delete()
{
    GCronEntry *this = THIS(GCronEntry_ID, "GCronEntry.delete");
    _(this->obj).delete();
    free(this);
}

static char TO_STRING_BUFF[100] = {};
static char *toString()
{
    GCronEntry *this = THIS(GCronEntry_ID, "GCronEntry.toString");
    sprintf(TO_STRING_BUFF, "GCronEntry(%s): msRepeat=%d, msLast=%d", this->obj->name, this->msRepeat, this->msLast);
    return TO_STRING_BUFF;
}

static void debug(char * message)
{
    GCronEntry *this = THIS(GCronEntry_ID, "GCronEntry.debug");
    printf("msRepeat: %d\n", _(this).msRepeat);
    printf("msLast: %d\n", _(this).msLast);
    printf("flags: %d\n", _(this).flags);
    printf("context: %p\n", _(this).context);
}

GCronEntry *GCronEntry_new(char * name, int msRepeat, int (*callback)(GCronEntry *self), void *context) {
    GCronEntry *this = NEW(GCronEntry);
    this->id = GCronEntry_ID;
    this->obj = GObj_new(name);
    this->msRepeat = msRepeat;
    this->msLast = GTimer.mSecs();
    this->callback = callback;
    this->context = context;
    
    this->debug = debug;
    this->delete = delete;
    this->toString = toString;

    return this;
}

