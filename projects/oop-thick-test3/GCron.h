#ifndef __GCron__
#define __GCron__

#include "GObj.h"
#include "GList.h"
#include "GCronEntry.h"

#define GCRON_DEACTIVATED 0x01

#define GCron_CLASS\
    GList *list;\
\
    METHOD(int, pump)();\
    METHOD(GCron *, add)(char *, int msRepeat, int (*callback)(GCronEntry *), void *context);

CLASS(GCron, GObj)

extern GCron *GCron_new(char * name);

#endif // __GCron__