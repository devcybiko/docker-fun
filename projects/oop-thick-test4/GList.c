#include "GList.h"

static void push(void *value)
{
    GList *this = THIS(GList_ID, "GList.push");
    printf("GList.push = %p\n", this->array);
    if (this->size == this->extent)
    {
        this->extent = this->extent * this->mult;
        this->array = REALLOC(this->array, this->extent, void *);
    }
    this->array[this->size++] = value;
}

static void *get(int n)
{
    GList *this = THIS(GList_ID, "GList.get");
    if (n < 0 || n >= this->size)
        return NULL;
    return this->array[n];
}

static void debug(char *message)
{
    GList *this = THIS(GList_ID, "GList.debug");
    _(this->obj).debug(message);
    printf("...this: %p\n", this);
    printf("...array: %p\n", this->array);
    printf("...extent: %d\n", this->extent);
    printf("...size: %d\n", this->size);
    printf("...mult: %f\n", this->mult);
    for (int i = 0; i < this->size; i++)
    {
        printf("... %d: %s\n", i, _(this).get(i));
    }
}

static void delete()
{
    GList *this = THIS(GList_ID, "GList.delete");
    _(this->obj).delete();
    free(this->array); // WARNING: memory leak if you don't delete the elements first
    free(this);
}

static char TO_STRING_BUFF[100] = {};
static char *toString()
{
    GList *this = THIS(GList_ID, "GList.toString");
    sprintf(TO_STRING_BUFF, "GList(%s): size=%d, extent=%d", this->obj->name, this->size, this->extent);
    return TO_STRING_BUFF;
}

GList *GList_new(char *name, int extent, double mult)
{
    GList *this = NEW(GList);
    printf("GList.new ...name: %s\n", name, extent, mult);

    this->id = GList_ID;
    this->obj = GObj_new(name);
    this->array = CALLOC(extent, void *);
    this->extent = extent == 0 ? 8 : extent;
    this->size = 0;
    this->mult = mult == 0.0 ? 2.0 : mult;

    this->debug = debug;
    this->delete = delete;
    this->toString = toString;
    this->get = get;
    this->push = push;

    return this;
}
