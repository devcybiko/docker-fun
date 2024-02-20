#ifndef __GTOS__
#define __GTOS__

#include "Object.h"
#include "List.h"

typedef struct GTosClass GTosClass;
typedef struct GTosObj GTosObj;

typedef struct {
    Object *obj;
} GTosObj;

typedef struct {
    ObjectClass *Object;
    GTosObj *(*new)(char *name, int extent, double mult);
    GTosClass *(*destroy)(GTosObj *obj);
    GTosClass *(*init)(GTosObj *obj, char *name, int extent, double mult);
    GTosClass *(*debug)(GTosObj *obj, char *args);
} GTosClass;

GTosClass *getGTosClass();


#endif // __GTOS__