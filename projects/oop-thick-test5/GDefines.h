#ifndef __GDefines__
#define __GDefines__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define NEW(TYPE) (TYPE *) calloc(1, sizeof(TYPE))
#define CALLOC(N, TYPE) (TYPE *)calloc(N, sizeof(TYPE));
#define MALLOC(N, TYPE) (TYPE *)malloc(N * sizeof(TYPE));
#define REALLOC(PTR, N, TYPE) (TYPE *)realloc(PTR, N * sizeof(TYPE));

#endif // __GDefines__