#include "Template.h"

static TemplateClass *debug(Template *this, char *args)
{
    DEBUG("  > debug\n");
    GObjClass->debug((GObj *) this, args);
    DEBUG(" < debug\n");
    return TEMPLATE;
}

static void destroy(Template *this)
{
    DEBUG("    > destroy\n");
    GObjClass->destroy((GObj *) this);
    free(this);
    DEBUG("    < destroy\n");
}

static TemplateClass *init(Template *this, char *name, int extent, double mult)
{
    DEBUG("    > init\n");
    GObjClass->init((GObj *) this, name);
    DEBUG("    < init\n");
    return TEMPLATE;
}

static Template *new(char *name, int extent, double mult)
{
    DEBUG("  > new\n");
    Template *this = NEW(Template);
    TEMPLATE->init(this, name, extent, mult);
    DEBUG("  < new\n");
    return this;
}

static TemplateClass _TEMPLATE = {
    .new = new,
    .init = init,
    .destroy = destroy,
    .debug = debug,
};

TemplateClass *TEMPLATE = &_TEMPLATE;