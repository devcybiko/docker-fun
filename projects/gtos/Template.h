#ifndef __TEMPLATE__
#define __TEMPLATE__

#include "GObj.h"

typedef struct TemplateClass TemplateClass;

typedef struct Template {
    GNAME name;
} Template;

typedef struct TemplateClass {
    Template *(*new)(char *name, int extent, double mult);
    void (*destroy)(Template *obj);
    TemplateClass *(*init)(Template *obj, char *name, int extent, double mult);
    TemplateClass *(*debug)(Template *obj, char *args);
} TemplateClass;

extern TemplateClass *TEMPLATE;

#endif // __TEMPLATE__
