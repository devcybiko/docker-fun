#ifndef __GDEFINES__
#define __GDEFINES__

#define __LINUX__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "Template.h"

#define NEW(TYPE) (TYPE *) malloc(sizeof(TYPE))
#define MALLOC(TYPE, n) (TYPE *) malloc(sizeof(TYPE) * n)
#define CALLOC(TYPE, n) (TYPE *) calloc(sizeof(TYPE), n)
#define REALLOC(TYPE, p, n) (TYPE *) realloc(p, sizeof(TYPE) * n)

#define DEBUG // printf

typedef char GNAME[16];

extern void *THIS;
extern void *SUPER;

#endif // __DEFINES__