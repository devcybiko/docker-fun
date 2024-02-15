#include "List.h"

static ListClass listClass;

static char *listGet(ListObj *this, int n)
{
    DEBUG("  > listGet %d\n", n);
    if (n < 0 || n >= this->list_size)
        return NULL;
    char *s = this->list_array[n];
    DEBUG("  < listGet  %d %s\n", n, s);
    return s;
}

static ListClass *listPush(ListObj *this, char *s)
{
    DEBUG("  > listPush %s\n", s);
    if (this->list_size == this->list_extent)
    {
        int new_extent = this->list_extent * this->list_mult;
        DEBUG("... List Extent ... %d -> %d\n", this->list_extent, new_extent);
        this->list_extent = new_extent;
        this->list_array = (char **)realloc(this->list_array, this->list_extent * sizeof(char *));
    }
    this->list_array[this->list_size++] = s;
    DEBUG("  < listPush %d %s\n", this->list_size - 1, s);
    return &listClass;
}

static ListClass *listDebug(ListObj *this, char *args)
{
    DEBUG("  > listDebug\n");
    this->obj->debug(this->obj, args);
    printf("List.list_array: %p\n", this->list_array);
    printf("List.list_extent: %d\n", this->list_extent);
    printf("List.list_size: %d\n", this->list_size);
    printf("List.list_mult: %f\n", this->list_mult);
    for (int i = 0; i < this->list_size; i++)
    {
        printf("... %d %s\n", i, listClass.get(this, i));
    }
    DEBUG(" < listDebug\n");
    return &listClass;
}

static void listDestroy(ListObj *this)
{
    DEBUG("    > listDestroy\n");
    this->obj->destroy(this->obj);
    free(this->list_array);
    free(this);
    DEBUG("    < listDestroy\n");
}

static ListClass *listInit(ListObj *this, char *name, int extent, double mult)
{
    DEBUG("    > listInit\n");
    this->obj = objectNew(name);
    this->list_size = 0;
    this->list_extent = extent;
    this->list_mult = mult;
    if (extent == 0)
        this->list_extent = 16;
    if (mult == 0.0)
        this->list_mult = 1.5;
    this->list_array = CALLOC(char *, this->list_extent);
    DEBUG("    < listInit\n");
    return &listClass;
}

ListObj *listNew(char *name, int extent, double mult)
{
    DEBUG("  > listNew\n");
    ListObj *this = NEW(ListObj);
    listClass.init(this, name, extent, mult);
    DEBUG("  < listNew\n");
    return this;
}

ListClass *getListClass()
{
    DEBUG("  > getList\n");
    listClass.new = listNew;
    listClass.init = listInit;
    listClass.destroy = listDestroy;
    listClass.debug = listDebug;
    listClass.push = listPush;
    listClass.get = listGet;
    DEBUG("  < getList\n");
    return &listClass;
}
