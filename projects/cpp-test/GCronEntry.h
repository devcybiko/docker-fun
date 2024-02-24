#ifndef __GCronEntry__
#define __GCronEntry__

#include "GObj.h"

class GCronEntry : public GObj
{
public:
    int msRepeat;
    int msLast;
    int flags;
    void *context;
    int (*callback)(GCronEntry *self);

    GCronEntry(std::string name, int msRepeat, int (*callback)(GCronEntry *self), void *context);
    ~GCronEntry();
    void debug(std::string message);
    std::string toString();
};

#endif // __GCronEntry__
