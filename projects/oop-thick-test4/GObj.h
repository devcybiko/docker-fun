#ifndef __GObj__
#define __GObj__

#include "Template.h"
#include "GDefines.h"

extern void *_THIS; // this
extern void *_this(); // _this

// echo -n "GObj" | xxd -ps
// 474f626a
#define GObj_ID 0x474f626a

typedef struct GObj GObj;
typedef struct GObj {
    int id;
    char name[16];
    METHOD(void, delete)();
    METHOD(void , debug)(char *message);
    METHOD(char *, toString)();
} GObj;

extern GObj *GObj_new(char *name);

#endif // __GObj__
