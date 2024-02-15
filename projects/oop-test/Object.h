#ifndef __OBJECT__
#define __OBJECT__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NEW(TYPE) (TYPE *) malloc(sizeof(TYPE))
#define MALLOC(TYPE, n) (TYPE *) malloc(sizeof(TYPE) * n)
#define CALLOC(TYPE, n) (TYPE *) calloc(sizeof(TYPE), n)

// #define DEBUG printf
#define DEBUG

typedef struct ObjectClass ObjectClass;
typedef struct Object Object;

typedef struct Object {
    char *name;
} Object;

typedef struct ObjectClass {
    Object *(*new)(char *name);
    ObjectClass *(*destroy)(Object *obj);
    ObjectClass *(*init)(Object *obj, char *name);
    ObjectClass *(*debug)(Object *obj, char *args);
} ObjectClass;

ObjectClass *getObjectClass();

#endif // __OBJECT__
