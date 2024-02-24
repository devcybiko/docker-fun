#ifndef __GCron__
#define __GCron__

#include "GObj.h"
#include "GList.h"
#include "GCronEntry.h"

#define GCRON_DEACTIVATED 0x01

class GCron : public GObj
{
public:
    GList *list;

    GCron(std::string name);
    ~GCron();
    void debug(std::string message);
    std::string toString();
    int pump();
    GCron *add(std::string, int msRepeat, int (*callback)(GCronEntry *), void *context);
};

#endif // __GCron__