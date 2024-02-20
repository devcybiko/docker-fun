#include "GList.h"

static void *get(GList *this, int n)
{
    DEBUG("  > get %d\n", n);
    if (n < 0 || n >= this->size)
        return NULL;
    void *s = this->array[n];
    DEBUG("  < get  %d %p\n", n, s);
    return s;
}

static GListClass *push(GList *this, void *s)
{
    DEBUG("  > push %p\n", s);
    DEBUG("  size=%d, extent=%d", this->size, this->extent);
    if (this->size == this->extent)
    {
        int new_extent = this->extent * this->mult;
        DEBUG("... List Extent ... %d -> %d\n", this->extent, new_extent);
        this->extent = new_extent;
        this->array = REALLOC(void *, this->array, this->extent);
    }
    this->array[this->size++] = s;
    DEBUG("  < push %d %p\n", this->size - 1, s);
    return GLIST;
}

static GListClass *debug(GList *this, char *args)
{
    DEBUG("  > debug\n");
    GOBJ->debug((GObj *) this, args);
    printf(".list_array: %p\n", this->array);
    printf(".list_extent: %d\n", this->extent);
    printf(".list_size: %d\n", this->size);
    printf(".list_mult: %f\n", this->mult);
    for (int i = 0; i < this->size; i++)
    {
        printf("... %d %p\n", i, GLIST->get(this, i));
    }
    DEBUG(" < debug\n");
    return GLIST;
}

static void destroy(GList *this)
{
    DEBUG("    > destroy\n");
    GOBJ->destroy((GObj *) this);
    free(this->array);
    free(this);
    DEBUG("    < destroy\n");
}

static GListClass *init(GList *this, char *name, int extent, double mult)
{
    DEBUG("    > init\n");
    GOBJ->init((GObj *) this, name);
    this->size = 0;
    this->extent = extent;
    this->mult = mult;
    if (extent == 0)
        this->extent = 16;
    if (mult == 0.0)
        this->mult = 1.5;
    this->array = CALLOC(void *, this->extent);
    DEBUG("    < init\n");
    return GLIST;
}

static GList *new(char *name, int extent, double mult)
{
    DEBUG("  > listNew\n");
    GList *this = NEW(GList);
    GLIST->init(this, name, extent, mult);
    DEBUG("  < listNew\n");
    return this;
}

static GListClass _GLIST = {
    .new = new,
    .init = init,
    .destroy = destroy,
    .debug = debug,
    .push = push,
    .get = get
};

GListClass *GLIST = &_GLIST;