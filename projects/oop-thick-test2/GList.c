#include "GList.h"

static GObj *_super = NULL;
#define EXTENDS(Obj) Obj *_super = NULL;
#define SUPER (THIS=this, _super)
#define INHERIT(Obj) if (!_super) super = Obj##_new("super");


static void push(void *value)
{
    GList *this = THIS;
    if (this->size == this->extent)
    {
        this->extent = this->extent * this->mult;
        this->array = (void **)realloc(this->array, this->extent * sizeof(void *));
    }
    this->array[this->size++] = value;
}

static void *get(int n)
{
    GList *this = THIS;
    if (n < 0 || n >= this->size)
        return NULL;
    return this->array[n];
}

static void debug(char *message)
{
    GList *this = THIS;
    SUPER->debug(message);
    printf("...name: %s\n", this->name);
    printf("...this: %p\n", this);
    printf("...array: %p\n", this->array);
    printf("...extent: %d\n", this->extent);
    printf("...size: %d\n", this->size);
    printf("...mult: %f\n", this->mult);
    for (int i = 0; i < this->size; i++)
    {
        printf("... %d: %s\n", i, this->get(i));
    }
}

static void delete()
{
    GList *this = THIS;
    free(this->array); // WARNING: memory leak if you don't delete the elements first
    free(this);
}

static char TO_STRING_BUFF[100] = {};

static char *toString()
{
    GList *this = THIS;
    sprintf(TO_STRING_BUFF, "GList(%s): size=%d, extent=%d", this->name, this->size, this->extent);
    return TO_STRING_BUFF;
}

static GList *init(char *name, int extent, double mult)
{
    GList *this = THIS;
    SUPER->init(name);
    printf("GList.init ...name: %s\n", this->name);

    this->delete = delete;
    this->toString = toString;
    this->get = get;
    this->debug = debug;
    this->push = push;

    this->array = (void *)calloc(sizeof(void *), extent);
    this->extent = extent == 0 ? 8 : extent;
    this->size = 0;
    this->mult = mult == 0.0 ? 2.0 : mult;
    _(this)->debug("GList.init");
    return this;
}

GList *GList_new(char *name, int extent, double mult)
{
    if (!_super) _super = GObj_new("super");
    GList *this = NEW(GList);
    this->init = init;
    return _(this)->init(name, extent, mult);
}
