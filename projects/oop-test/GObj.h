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

#define DEBUG printf

typedef struct GObjClass GObjClass;
typedef char GNAME[16];
typedef int (*GFunc)();

extern void *THIS;
extern void *SUPER;

typedef struct GObj {
    GNAME name;
    GObjClass *class;
    GObjClass *super;
} GObj;

typedef struct GObjClass {
    GObj *(*new)(char *name, void *class);
    GObjClass *(*init)(char *name);
    void (*destroy)();
    GObjClass *(*debug)(char *args);
} GObjClass;

extern const GObjClass *GObj$;
extern const GObjClass _GObj$;

#define _(OBJ) (THIS=OBJ, OBJ->class)
#define __(OBJ) (THIS=OBJ, OBJ->super)
#endif // __OBJECT__
