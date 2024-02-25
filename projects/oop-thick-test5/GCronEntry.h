#ifndef __GCronEntry__
#define __GCronEntry__

#include "GObj.h"

// echo -n "GCronEntry" | xxd -ps
// 4743726f6e456e747279
#define GCronEntry_ID 0x4743726f6e456e747279

CLASS(GCronEntry)
    GObj_CLASS
    int msRepeat; 
    int msLast; 
    int flags; 
    void *context; 
    int (*callback)(GCronEntry *self);
CLASS_END(GCronEntry);

extern GCronEntry *GCronEntry_new_full(char * name, int msRepeat, int (*callback)(GCronEntry *self), void *context);
extern GCronEntry *GCronEntry_new(int msRepeat, int (*callback)(GCronEntry *self), void *context);

#endif // __GCronEntry__
