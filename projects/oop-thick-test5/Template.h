#ifndef __Template__
#define __Template__

#define _(Obj) (_THIS_=Obj, *(Obj))
#define THIS(Obj_ID, NAME)  _this(Obj_ID, NAME)
#define _THIS(Obj_ID, NAME)  _this(GObj_ID, NAME) // special GObj version

#define CLASS(Obj) \
typedef struct Obj Obj; \
typedef struct Obj {

#define CLASS_END(Obj) \
} Obj;

#define NAME char name[16]

#define METHOD(TYPE, NAME) TYPE (*NAME)

#endif // __Template__