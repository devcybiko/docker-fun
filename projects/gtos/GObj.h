#ifndef __OBJECT__
#define __OBJECT__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define NEW(TYPE) (TYPE *) malloc(sizeof(TYPE))
#define MALLOC(TYPE, n) (TYPE *) malloc(sizeof(TYPE) * n)
#define CALLOC(TYPE, n) (TYPE *) calloc(sizeof(TYPE), n)
#define REALLOC(TYPE, p, n) (TYPE *) realloc(p, sizeof(TYPE) * n)

// #define DEBUG printf
#define DEBUG

typedef struct GObjClass GObjClass;
typedef char GNAME[16];
typedef int (*GFunc)();

typedef struct GObj {
    GNAME name;
} GObj;

typedef struct GObjClass {
    GObj *(*new)(char *name);
    GObjClass *(*destroy)(GObj *obj);
    GObjClass *(*init)(GObj *obj, char *name);
    GObjClass *(*debug)(GObj *obj, char *args);
} GObjClass;

extern GObjClass *GOBJ;

#endif // __OBJECT__
