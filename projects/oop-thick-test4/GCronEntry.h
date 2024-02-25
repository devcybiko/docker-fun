#ifndef __GCronEntry__
#define __GCronEntry__

#include "GObj.h"

#define GCronEntry_CLASS \
    int msRepeat; \
    int msLast; \
    int flags; \
    void *context; \
    int (*callback)(GCronEntry *self);

CLASS(GCronEntry, GObj)

extern GCronEntry *GCronEntry_new(char * name, int msRepeat, int (*callback)(GCronEntry *self), void *context);

#endif // __GCronEntry__
