#include "List.h"

static ListClass listClass;

static void *listGet(void *_this, int n) {
    DEBUG("  > listGet %d\n", n);
    ListInstance *this = _this;
    if (n < 0 || n >= this->list_size) return NULL;
    void *p = this->list_array[n];
    DEBUG("  < listGet %p\n", p);
    return p;
}

static void listPush(void *_this, void *p) {
    DEBUG("  > listPush %p\n", p);
    ListInstance *this = _this;
    double MULT = 1.5;
    this->list_array[this->list_size++] = p;
    if (this->list_size == this->list_extent) {
        printf("... List Extent ... %d -> %d\n", this->list_extent, (int) (this->list_extent * MULT));
        this->list_extent *= MULT;
        this->list_array = (void **)realloc(this->list_array, this->list_extent * sizeof(void *));
    }
    DEBUG("  < listPush\n");
}

static void listDebug(void *_this, char *args) {
    ListInstance *this = _this;
    listClass.super->debug(this, args);
    printf("List.list_array: %p\n", this->list_array);
    printf("List.list_extent: %d\n", this->list_extent);
    printf("List.list_size: %d\n", this->list_size);
    for(int i=0; i<this->list_size; i++) {
        printf("... %d %p\n", i, listClass.get(this, i));
    }
}

static void listDestroy(void *_this) {
    ListInstance *this = _this;
    DEBUG("    > listDestroy\n");
    free(this->list_array);
    listClass.super->destroy(this);
    DEBUG("    < listDestroy\n");
}

static void listInit(void *_this, char *name) {
    ListInstance *this = _this;
    DEBUG("    > listInit\n");
    listClass.super->init(this, name);
    this->list_size = 0;
    this->list_extent = 10;
    this->list_array = CALLOC(void *, this->list_extent);
    DEBUG("    < listInit\n");
}

static ListInstance *listNew(char *name) {
    DEBUG("  > listNew\n");
    ListInstance *this = NEW(ListInstance);
    listClass.init(this, name);
    DEBUG("  < listNew\n");
    return this;
}

ListClass *getListClass() {
    listClass.super = getObjectClass();
    listClass.new = listNew;
    listClass.init = listInit;
    listClass.destroy = listDestroy;
    listClass.debug = listDebug;
    listClass.push = listPush;
    listClass.get = listGet;
    return &listClass;
}
