#ifndef __Template__
#define __Template__

#define NEW(TYPE) (TYPE *) calloc(1, sizeof(TYPE))
#define CALLOC(N, TYPE) (TYPE *)calloc(N, sizeof(TYPE));

#define _(Obj) (THIS=Obj, Obj)

#define CLASS(Obj, Super) \
typedef struct Obj Obj; \
typedef struct Obj { \
    Super##_CLASS \
    Obj##_CLASS \
} Obj;

#define ROOT_CLASS(Obj) \
typedef struct Obj Obj; \
typedef struct Obj { \
    Obj##_CLASS \
} Obj;

#define EXTENDS(Obj) Obj *_super = NULL;
#define SUPER (THIS=this, _super)
#define INHERIT_FROM(Obj) if (!_super) _super = Obj##_new("super");

#endif // __Template__