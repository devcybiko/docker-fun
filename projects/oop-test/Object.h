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

typedef struct Object Object;

typedef struct Object {
    char *name;
    void (*destroy)(Object *obj);\
    Object *(*init)(Object *obj, char *name);\
    Object *(*debug)(Object *obj, char *args);
} Object;

Object *objectNew(char *name);

#endif // __OBJECT__
