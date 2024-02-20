#include "GCron.h"
#include "GTimer.h"

static GCronClass* debug(GCron* this, char* args)
{
    DEBUG("  > debug\n");
    GOBJ->debug((GObj*)this, args);
    DEBUG(" < debug\n");
    return GCRON;
}

static void destroy(GCron* this)
{
    DEBUG("    > destroy\n");
    GOBJ->destroy((GObj*)this);
    free(this);
    DEBUG("    < destroy\n");
}

static GCronClass* init(GCron* this, char* name, int msRepeat, GFunc callback, void* context)
{
    DEBUG("    > init\n");
    GOBJ->init((GObj*)this, name);
    this->msRepeat = msRepeat;
    this->msLast = GTIMER->mSecs();
    this->callback = callback;
    this->context = context;
    DEBUG("    < init\n");
    return GCRON;
}

static inline void initList() {
    if (!GCRON->list) GCRON->list = GLIST->new("cronlist", 8, 2);
}

static GCron* new(char* name, int msRepeat, GFunc callback, void* context)
{
    DEBUG("  > new\n");
    initList();
    GCron* this = NEW(GCron);
    GCRON->init(this, name, msRepeat, callback, context);
    GLIST->push(GCRON->list, this);
    DEBUG("  < new\n");
    return this;
}

static GCronClass* pump()
{
    // DEBUG("  > pump\n");
    initList();
    int now = GTIMER->mSecs(); // get current time in mSecs
    for (int i = 0; i < GCRON->list->size; i++) {
        GCron* obj = (GCron*)GLIST->get(GCRON->list, i);
        if (obj && !(obj->flags & GCRON_DEACTIVATED)) {
            DEBUG("now=%d, msLast=%d, msRepeat=%d, %d\n", now, obj->msLast, obj->msRepeat, obj->msLast + obj->msRepeat < now);
            if (obj->msLast + obj->msRepeat < now) {
                int newFlags = obj->callback(obj);
                obj->flags = newFlags;
                obj->msLast = now;
            }
        }
    }
    // DEBUG("  < pump\n");
    return GCRON;
}

static GCronClass _GCRON = {
    .new = new,
    .init = init,
    .destroy = destroy,
    .debug = debug,
    .pump = pump,
    .list = NULL,
};

GCronClass* GCRON = &_GCRON;