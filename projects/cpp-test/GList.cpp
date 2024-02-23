#include "GList.h"

GList::GList(std::string name, int extent, double mult) : GObj(name)
{
    this->size = 0;
    this->extent = extent;
    this->mult = mult;
    if (extent == 0)
        this->extent = 16;
    if (mult == 0.0)
        this->mult = 1.5;
    this->array = (void **)calloc(this->extent, sizeof(void *));
}

GList::~GList()
{
    free(this->array);
}

GList *GList::push(void *value)
{
    if (this->size == this->extent)
    {
        this->extent = this->extent * this->mult;
        this->array = (void **)realloc(this->array, this->extent * sizeof(void *));
    }
    this->array[this->size++] = value;
    return this;
}

void *GList::get(int n)
{
    if (n < 0 || n >= this->size)
        return NULL;
    return this->array[n];
}

void GList::debug(std::string message)
{
    GObj::debug(message);
    printf(".list_array: %p\n", this->array);
    printf(".list_extent: %d\n", this->extent);
    printf(".list_size: %d\n", this->size);
    printf(".list_mult: %f\n", this->mult);
    for (int i = 0; i < this->size; i++)
    {
        printf("... %d %p\n", i, this->get(i));
    }
}

std::string GList::toString()
{
    return this->name +"," + std::to_string(this->size);
}
