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

#define _(Obj) (THIS=Obj, Obj)

#endif // __GDefines__