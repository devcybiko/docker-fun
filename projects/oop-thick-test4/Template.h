#ifndef __Template__
#define __Template__

#define _(Obj) (_THIS=Obj, *(Obj))
#define THIS(Obj_ID, NAME)  _this(Obj_ID, NAME)

#define CLASS(Obj) \
typedef struct Obj Obj; \
typedef struct Obj {

#define CLASS_END(Obj) \
} Obj;

#define METHOD(TYPE, NAME) TYPE (*NAME)

#endif // __Template__