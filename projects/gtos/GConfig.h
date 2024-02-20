#ifndef __GCONFIG__
#define __GCONFIG__

#include "GObj.h"

typedef struct GConfigClass GConfigClass;

typedef struct GConfig {
    GNAME name;
} GConfig;

typedef struct GConfigClass {
    GConfig *(*new)(char *name, int extent, double mult);
    void (*destroy)(GConfig *obj);
    GConfigClass *(*init)(GConfig *obj, char *name, int extent, double mult);
    GConfigClass *(*debug)(GConfig *obj, char *args);
} GConfigClass;

extern GConfigClass *GCONFIG;

#endif // __GCONFIG__
