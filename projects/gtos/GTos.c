#include "GTos.h"
#include "GTimer.h"

static GTosClass gtosClass;

static GTosClass *gtosDebug(GTosObj *this, char *args)
{
    DEBUG("  > gtosDebug\n");
    gtosClass.Object->debug(this->obj, args);
    return &gtosClass;
}

static void gtosDestroy(GTosObj *this)
{
    DEBUG("    > gtosDestroy\n");
    gtosClass.Object->destroy(this->obj);
    free(this);
    DEBUG("    < gtosDestroy\n");
}

static GTosClass *gtosInit(GTosObj *this, char *name, int extent, double mult)
{
    DEBUG("    > gtosInit\n");
    this->obj = gtosClass.Object->new(name);
    DEBUG("    < gtosInit\n");
    return &gtosClass;
}

GTosObj *gtosNew(char *name, int extent, double mult)
{
    DEBUG("  > gtosNew\n");
    GTosObj *this = NEW(GTosObj);
    gtosClass.init(this, name, extent, mult);
    DEBUG("  < gtosNew\n");
    return this;
}

GTosClass *getGTosClass()
{
    DEBUG("  > getGTos\n");
    gtosClass.Object = getObjectClass();
    gtosClass.new = gtosNew;
    gtosClass.init = gtosInit;
    gtosClass.destroy = gtosDestroy;
    gtosClass.debug = gtosDebug;
    DEBUG("  < getGTos\n");
    return &gtosClass;
}
