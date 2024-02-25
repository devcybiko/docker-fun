#ifndef __GCron__
#define __GCron__

#include "GObj.h"
#include "GList.h"
#include "GCronEntry.h"

#define GCRON_DEACTIVATED 0x01

// echo -n "GCron" | xxd -ps
// 4743726f6e
#define GCron_ID 0x4743726f6e

CLASS(GCron)
    GObj_CLASS
    GList *list;

    METHOD(int, pump)();
    METHOD(GCron *, add)(char *, int msRepeat, int (*callback)(GCronEntry *), void *context);

CLASS_END(GCron)

extern GCron *GCron_new(char * name);

#endif // __GCron__