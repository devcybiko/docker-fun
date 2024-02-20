#ifndef __CRON__
#define __CRON__

#include "GObj.h"
#include "GList.h"

typedef struct GCronClass GCronClass;

#define GCRON_DEACTIVATED 0x01

typedef struct GCron {
    GNAME name;
    int (*callback)(struct GCron *);
    int msRepeat;
    int msLast;
    int flags;
    void *context;
} GCron;

typedef struct GCronClass {
    GCron *(*new)(char *name, int msRepeat, GFunc callback, void *context);
    void (*destroy)(GCron *obj);
    GCronClass *(*init)(GCron *obj, char *name, int msRepeat, GFunc callback, void *context);
    GCronClass *(*debug)(GCron *obj, char *args);
    GCronClass *(*pump)();
    GList *list;
} GCronClass;

extern GCronClass *GCRON;

#endif // __CRON__
