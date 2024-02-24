#ifndef __GCronEntry__
#define __GCronEntry__

#include "GObj.h"

#define GCronEntry_MEMBERS(Obj, SuperObj) \
    int (*callback)(struct GCronEntry *); \
    int msRepeat; \
    int msLast; \
    int flags; \
    void *context;

#define GCronEntry_CONSTRUCTOR(Obj, SuperObj) \
    GCronEntry *(*new)(char *name, int msRepeat, GFunc callback, void *context); \
    GCronEntryClass *(*init)(char *name, int msRepeat, GFunc callback, void *context);

#define GCronEntry_METHODS(Obj, SuperObj) \

CLASS(GCronEntry, GObj)

#endif // __GCronEntry__
