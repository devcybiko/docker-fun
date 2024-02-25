#include "GList.h"

#define DEBUG // printf

static void push(GObj *value)
{
    GList *this = THIS(GList_ID, "GList.push");
    DEBUG("GList.push = %s\n", this->name);
    if (!this->safe) DEBUG("...value = %p\n", value);
    else DEBUG("... value = %p\n", value);
    if (this->size == this->extent)
    {
        this->extent = this->extent * this->mult;
        this->array = REALLOC(this->array, this->extent, GObj *);
    }
    this->array[this->size++] = value;
    DEBUG("...size = %d\n", this->size);
}

static int set(int n, void *value)
{
    GList *this = THIS(GList_ID, "GList.push");
    DEBUG("GList.push = %p\n", this->array);
    if (n > this->size) return -1;
    this->array[n] = value;
    return n;
}

static GObj *get(int n)
{
    GList *this = THIS(GList_ID, "GList.get");
    if (n < 0 || n >= this->size)
        return NULL;
    return this->array[n];
}

static void debug(char *message)
{
    GList *this = THIS(GList_ID, "GList.debug");
    DEBUG("GList: %s\n", this->name);
    DEBUG("...this: %p\n", this);
    DEBUG("...array: %p\n", this->array);
    DEBUG("...extent: %d\n", this->extent);
    DEBUG("...size: %d\n", this->size);
    DEBUG("...mult: %f\n", this->mult);
    for (int i = 0; i < this->size; i++)
    {
        GObj *obj = _(this).get(i);
        DEBUG("... %d: %p\n", i, obj);
    }
}

static void delete()
{
    GList *this = THIS(GList_ID, "GList.delete");
    if (this->safe)
    {
        _(this).safeDelete();
        return;
    }
    for(int i = 0; i < this->size; i++)
    {
        _(this->array[i]).delete();
    }
    free(this->array);
    free(this);
}

static void safeDelete()
{
    GList *this = THIS(GList_ID, "GList.safeDelete");
    DEBUG("GList.safeDelete: safe mode\n");
    free(this->array);
    free(this);
}

static char *toString()
{
    GList *this = THIS(GList_ID, "GList.toString");
    sprintf(GObj_stringbuffer, "GList(%s): size=%d, extent=%d", this->name, this->size, this->extent);
    return GObj_stringbuffer;
}

GList *GList_new_full(char *name, int extent, double mult)
{
    GList *this = NEW(GList);
    DEBUG("GList.new ...name: %s\n", name, extent, mult);

    GObj_init(this, name, GList_ID);
    this->array = CALLOC(extent, void *);
    this->extent = extent == 0 ? 8 : extent;
    this->size = 0;
    this->mult = mult == 0.0 ? 2.0 : mult;
    this->safe = false; // set this to TRUE to prevent delete from freeing the objects

    this->debug = debug;
    this->delete = delete;
    this->toString = toString;
    this->get = get;
    this->push = push;
    this->safeDelete = safeDelete;

    return this;
}

GList *GList_new(char *name)
{
    return GList_new_full("GList", 0, 0.0);
}