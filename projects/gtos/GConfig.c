#include "GConfig.h"

static GConfigClass *debug(GConfig *this, char *args)
{
    DEBUG("  > debug\n");
    GOBJ->debug((GObj *) this, args);
    DEBUG(" < debug\n");
    return GCONFIG;
}

static void destroy(GConfig *this)
{
    DEBUG("    > destroy\n");
    GOBJ->destroy((GObj *) this);
    free(this);
    DEBUG("    < destroy\n");
}

static GConfigClass *init(GConfig *this, char *name, int extent, double mult)
{
    DEBUG("    > init\n");
    GOBJ->init((GObj *) this, name);
    DEBUG("    < init\n");
    return GCONFIG;
}

GConfig *new(char *name, int extent, double mult)
{
    DEBUG("  > new\n");
    GConfig *this = NEW(GConfig);
    GCONFIG->init(this, name, extent, mult);
    DEBUG("  < new\n");
    return this;
}

static GConfigClass _GCONFIG = {
    .new = new,
    .init = init,
    .destroy = destroy,
    .debug = debug,
};

GConfigClass *GCONFIG = &_GCONFIG;