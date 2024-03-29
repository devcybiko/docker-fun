#ifndef __Tps65__
#define __Tps65__

#include "GObj.h"
#include "GList.h"

// echo -n "Tps65" | xxd -ps
// 4743726f6e
#define Tps65_ID 0x43726f6e

#define Tps65_MEMBERS(Obj, SuperObj) \
    GList *list;

#define Tps65_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id);

#define Tps65_METHODS(Obj, SuperObj) \
    METHOD(int, pump)(void); \
    METHOD(Tps65Entry *, add)(int msRepeat, FUNC(int, callback, Tps65Entry*), void *context);

CLASS(Tps65, GObj)

extern Tps65* Tps65_new(void);

#endif // __Tps65__
