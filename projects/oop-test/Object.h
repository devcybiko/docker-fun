#ifndef __OBJECT__
#define __OBJECT__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NEW(TYPE) (TYPE *) malloc(sizeof(TYPE))
#define MALLOC(TYPE, n) (TYPE *) malloc(sizeof(TYPE) * n)
#define CALLOC(TYPE, n) (TYPE *) calloc(sizeof(TYPE), n)

#define DEBUG

typedef struct ObjectClass ObjectClass;
typedef struct ObjectInstance ObjectInstance;

#define OBJECT_METHODS \
    void (*init)(void *obj, char *name);\
    void (*destroy)(void *obj);\
    void (*debug)(void *obj, char *args);

typedef struct ObjectClass {
    void *super;
    ObjectInstance *(*new)(char *name);
    OBJECT_METHODS
} ObjectClass;

#define OBJECT_MEMBERS \
    char *name;

typedef struct ObjectInstance {
    OBJECT_MEMBERS
} ObjectInstance;

ObjectClass *getObjectClass();

#define NEW_CLASS(NewClass, getNewClass, NewInstance) \
typedef struct NewClass {\
    ParentClass *super;\
    NewInstance *(*new)(char *name);\
    PARENT_METHODS\
    NEW_METHODS\
} NewClass;\
NewClass *getNewClass();

#define NEW_INSTANCE(NewInstance) \
typedef struct NewInstance {\
    PARENT_MEMBERS\
    NEW_MEMBERS\
} NewInstance;

#endif // __OBJECT__
