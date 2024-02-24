#include "GList.h"

static GList *new(char *name, int extent, double mult)
{
    DEBUG("> GList.new %s\n", name);
    GList *this = NEW(GList);
    this->class = GList$;
    this->super = GListSuper$;
    _(this)->init(name, extent, mult);
    DEBUG("< GList.new %s\n", name);
    return this;
}

static GListClass *init(char *name, int extent, double mult)
{
    GList *this = THIS;
    DEBUG("> GList.init %s\n", name);
    __(this)->init(name);
    this->size = 0;
    this->extent = extent;
    this->mult = mult;
    if (extent == 0)
        this->extent = 16;
    if (mult == 0.0)
        this->mult = 1.5;
    this->array = CALLOC(void *, this->extent);
    DEBUG("< GList.init\n");
    return _(this);
}

static void *get(int n)
{
    GList *this = THIS;
    DEBUG("> GList.get %d\n", n);
    if (n< 0 || n>= this->size)
        return NULL;
    void *s = this->array[n];
    DEBUG("< GList.get  %d %p\n", n, s);
    _(this);
    return s;
}

static GListClass *push(void *s)
{
    GList *this = THIS;
    DEBUG(" > push %p\n", s);
    DEBUG("  array=%p size=%d, extent=%d\n", this->array, this->size, this->extent);
    if (this->size == this->extent)
    {
        int new_extent = this->extent * this->mult;
        DEBUG("... List Extent ... %d -> %d\n", this->extent, new_extent);
        this->extent = new_extent;
        this->array = REALLOC(void *, this->array, this->extent);
    }
    DEBUG("24...\n");
    this->array[this->size++] = s;
    DEBUG(" < push %d %p\n", this->size - 1, s);
    return _(this);
}

static GListClass *debug(char *args)
{
    GList *this = THIS;
    DEBUG("> GList.debug\n");
    __(this)->debug(args);
    printf(".list_array: %p\n", this->array);
    printf(".list_extent: %d\n", this->extent);
    printf(".list_size: %d\n", this->size);
    printf(".list_mult: %f\n", this->mult);
    for (int i = 0; i< this->size; i++)
    {
        printf("... %d %p\n", i, _(this)->get(i));
    }
    DEBUG("< GList.debug\n");
    return _(this);
}

static GListClass *delete()
{
    GList *this = THIS;
    DEBUG("> GList.delete\n");
    __(this)->delete();
    free(this->array);
    free(this);
    DEBUG("< GList.delete\n");
}

const GListClass _GList$ = {
    .new = new,
    .init = init,
    .delete = delete,
    .debug = debug,
    .push = push,
    .get = get
};

GListClass *GList$ = &_GList$;
GObjClass *GListSuper$ = &_GObj$;