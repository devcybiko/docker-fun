#ifndef __GObj__
#define __GObj__

#include "Template.h"
#include "GDefines.h"

extern void *_THIS_; // this
extern void *_this(); // _this

// echo -n "GObj" | xxd -ps
// 474f626a
#define GObj_ID 0x474f626a

#define GObj_CLASS \
    int id; \
    NAME; \
    METHOD(void, delete)(); \
    METHOD(void , debug)(char *message); \
    METHOD(char *, toString)();

CLASS(GObj)
    GObj_CLASS
CLASS_END(GObj);

extern GObj *GObj_new(char *name);
extern char GObj_stringbuffer[];

#endif // __GObj__
