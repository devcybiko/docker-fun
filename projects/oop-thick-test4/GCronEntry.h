#ifndef __GCronEntry__
#define __GCronEntry__

#include "GObj.h"

// echo -n "GCronEntry" | xxd -ps
// 4743726f6e456e747279
#define GCronEntry_ID 0x4743726f6e456e747279

CLASS(GCronEntry)
    int id;
    GObj *obj;
    int msRepeat; 
    int msLast; 
    int flags; 
    void *context; 
    int (*callback)(GCronEntry *self);

    METHOD(void, delete)();
    METHOD(void , debug)(char *message);
    METHOD(char *, toString)();

CLASS_END(GCronEntry);

extern GCronEntry *GCronEntry_new(char * name, int msRepeat, int (*callback)(GCronEntry *self), void *context);

#endif // __GCronEntry__
