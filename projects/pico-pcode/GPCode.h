#ifndef __GPCode__
#define __GPCode__

#include "./gtos/GObj.h"

// echo -n "Code" | xxd -ps
#define GPCode_ID 0x436f6465

#define GPCode_MEMBERS(Obj, SuperObj) \
    GList *list;

#define GPCode_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id);

#define GPCode_METHODS(Obj, SuperObj) \
    METHOD(int, pump)(void); \
    METHOD(GPCodeEntry *, add)(int msRepeat, FUNC(int, callback, GPCodeEntry*), void *context);

CLASS(GPCode, GObj)

extern GPCode* GPCode_new(void);

#endif // __GPCode__
