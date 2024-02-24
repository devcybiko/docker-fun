#ifndef __TEMPLATE__
#define __TEMPLATE__

#define CLASS_NAME(Obj) Obj##Class
#define _CLASS_NAME(Obj) _##_CLASS##Class 
#define METHOD(TYPE, NAME) TYPE(*NAME)

#define MEMBERS(Obj, SuperObj) \
typedef struct CLASS_NAME(Obj) CLASS_NAME(Obj); \
typedef struct Obj { \
    SuperObj##_MEMBERS(Obj, SuperObj) \
    Obj##_MEMBERS(Obj, SuperObj) \
} Obj;

#define METHODS(Obj, SuperObj) \
typedef struct CLASS_NAME(Obj) { \
    Obj##_CONSTRUCTOR(Obj, Obj) \
    SuperObj##_METHODS(Obj, SuperObj) \
    Obj##_METHODS(Obj, SuperObj) \
} CLASS_NAME(Obj);

#define CLASS(Obj, SuperObj) \
MEMBERS(Obj, SuperObj) \
METHODS(Obj, SuperObj) \
CONSTANTS(Obj, SuperObj)

#define CONSTANTS(Obj, SuperObj) \
extern CLASS_NAME(Obj) *Obj##$; \
extern const CLASS_NAME(Obj) _##Obj##$; \
extern CLASS_NAME(SuperObj) *Obj##Super$;

//// Root Objects

#define _MEMBERS(Obj) \
typedef struct CLASS_NAME(Obj) CLASS_NAME(Obj); \
typedef struct Obj { \
    Obj##_MEMBERS(Obj, Obj) \
} Obj;

#define _METHODS(Obj) \
typedef struct CLASS_NAME(Obj) { \
    Obj##_CONSTRUCTOR(Obj, Obj) \
    Obj##_METHODS(Obj, Obj) \
} CLASS_NAME(Obj);

#define _CONSTANTS(Obj) \
extern CLASS_NAME(Obj) *Obj##$; \
extern const Obj##Class _##Obj##$;

#define _CLASS(Obj) \
_MEMBERS(Obj) \
_METHODS(Obj) \
_CONSTANTS(Obj)


// _(this)->method(...) == Call Method 
// __(this)->method(...) == Call Super Method

#define START_LINKAGES(Obj, SuperObj) const CLASS_NAME(Obj) _##Obj##$ = {
#define LINKAGE(Func) . Func = Func,
#define END_LINKAGES(Obj, SuperObj) \
}; \
CLASS_NAME(Obj) *Obj##$ = &_##Obj##$; \
CLASS_NAME(SuperObj) *Obj##Super$ = &_##SuperObj##$;

// CALL Directives
#define _(Obj) (THIS=Obj, Obj->class)
#define __(Obj) (THIS=Obj, Obj->super)

#endif // __TEMPLATE__