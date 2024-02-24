#ifndef __CRON__
#define __CRON__

#include "GObj.h"
#include "GList.h"
#include "GCronEntry.h"

#define GCRON_DEACTIVATED 0x01

#define GCron_MEMBERS(Obj, SuperObj) \
    GList *list;

#define GCron_CONSTRUCTOR(Obj, SuperObj) \
    GCron *(*new)(char *name); \
    GCronClass *(*init)(char *name);

#define GCron_METHODS(Obj, SuperObj) \
    METHOD(int, pump)(); \
    GCronClass *(*add)(char *name, int msRepeat, int (*callback)(), void *context);

CLASS(GCron, GObj)

#endif // __CRON__
