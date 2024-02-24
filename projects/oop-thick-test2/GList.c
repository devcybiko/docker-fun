#include "GList.h"


// GList::~GList()
// {
//     free(this->array);
// }

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

static char TO_STRING_BUFF[100]={};

static char *toString()
{
    GList *this = THIS;
    // sprintf(TO_STRING_BUFF, "GList(%s): size=%d, extent=%d", this->name, this->size, this->extent);
    printf("%s\n", "xxx");
    return TO_STRING_BUFF;
}

GList *GList_new(char *name, int extent, double mult) {
printf("GList_new\n");
    GList *this = NEW(GList);
    printf("GList_new %p\n", this);
    GObj_init(this, name);
    printf("GList_new %p\n", this);
    this->toString = toString;
    printf("GList_new->string %p\n", this->toString);

    this->size = 0;
    this->extent = extent;
    this->mult = mult;
    if (extent == 0)
        this->extent = 16;
    if (mult == 0.0)
        this->mult = 1.5;
    this->array = CALLOC(this->extent, void *);
    printf("GList_new %p\n", this);
    return this;
}
