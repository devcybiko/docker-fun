#include "GList.h"



// GList *GList::push(void *value)
// {
//     if (this->size == this->extent)
//     {
//         this->extent = this->extent * this->mult;
//         this->array = (void **)realloc(this->array, this->extent * sizeof(void *));
//     }
//     this->array[this->size++] = value;
//     return this;
// }

// void *GList::get(int n)
// {
//     if (n < 0 || n >= this->size)
//         return NULL;
//     return this->array[n];
// }

// void GList::debug(std::string message)
// {
//     GObj::debug(message);
//     cout << ".list_array: " << this->array << endl;
//     cout << ".list_extent: " << this->extent << endl;
//     cout << ".list_size: " << this->size << endl;
//     cout << ".list_mult: " << this->mult << endl;
//     for (int i = 0; i < this->size; i++)
//     {
//         cout << "... " << i << " " << this->get(i) << endl;
//     }
// }

static void delete()
{
    GList *this = THIS;
    free(this->array); // WARNING: memory leak if you don't delete the elements first
    free(this);
}

static char TO_STRING_BUFF[100]={};

static char *toString()
{
    GList *this = THIS;
    sprintf(TO_STRING_BUFF, "GList(%s): size=%d, extent=%d", this->name, this->size, this->extent);
    return TO_STRING_BUFF;
}

static GObj *super = NULL;

static GList *init(char *name, int extent, double mult)
{
    GList *this = THIS;
    _(super)->init(name);

    this->delete = delete;
    this->toString = toString;
    this->array = (void *)calloc(sizeof(void *), extent);
    this->extent = extent;
    this->size = 0;
    this->mult = mult;
    return this;
}

GList *GList_new(char *name, int extent, double mult) {
    if (!super) super = GObj_new("super");
    GList *this = NEW(GList);
    this->init = init;
    return _(this)->init(name, extent, mult);
}
