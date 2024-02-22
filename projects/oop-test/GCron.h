#ifndef __CRON__
#define __CRON__

#include "GObj.h"
#include "GList.h"

typedef struct GCronClass GCronClass;

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

typedef struct GCron
{
    GNAME name;
    GCronClass *class;
    GObjClass *super;
    GList *list;
} GCron;

typedef struct GCronClass
{
    GCron *(*new)(char *name);
    GCronClass *(*init)(char *name);
    void (*destroy)();
    GCronClass *(*debug)(char *args);
    GCronClass *(*pump)();
    GCronClass *(*add)(char *name, int msRepeat, int (*callback)(), void *context);
} GCronClass;

extern GCronClass *GCron$;
extern GObjClass *GCronSuper$;

#endif // __CRON__
