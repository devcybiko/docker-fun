#ifndef __CRON__
#define __CRON__

#include "GObj.h"
#include "GList.h"

#define GCRON_DEACTIVATED 0x01

typedef struct GCronEntry
{
    GNAME name;
    GObjClass *class;
    GObjClass *super;
    int (*callback)(struct GCronEntry *);
    int msRepeat;
    int msLast;
    int flags;
    void *context;
} GCronEntry;

#define GCron_MEMBERS(Obj, SuperObj) \
    GList *list;

#define GCron_CONSTRUCTOR(Obj, SuperObj) \
    GCron *(*new)(char *name); \
    GCronClass *(*init)(char *name);

#define GCron_METHODS(Obj, SuperObj) \
    GCronClass *(*pump)(); \
    GCronClass *(*add)(char *name, int msRepeat, int (*callback)(), void *context); \

CLASS(GCron, GObj)

#endif // __CRON__
