#define TRACE_OFF

#include "GList.h"

GList* GList_new_full(int extent, double mult)
{
    if (GList$.id == 0) _initClass();
    GList* this = NEW(GList);
    this->class = &GList$;
    _(this).init(GList_ID, extent, mult);
    return this;
}

GList* GList_new(void)
{
    GList* this = GList_new_full(0, 0);
    return this;
}

static void init(int id, int extent, double mult) {
    GList* this = _THIS_; // special case for init
    __(this).init(id);
    this->size = 0;
    this->extent = extent;
    this->mult = mult;
    if (extent == 0) this->extent = 8;
    if (mult == 0.0) this->mult = 2.0;
    this->array = CALLOC(this->extent, void*);
}

static void* get(int n) {
    GList* this = THIS(GList, "GList.toString");
    void *result = NULL;
    if (0 <= n && n < this->size) {
        result = this->array[n];
    }
    return result;
}

static void push(void* s) {
    GList* this = THIS(GList, "GList.push");
    if (this->size == this->extent) {
        int new_extent = this->extent * this->mult;
        this->extent = new_extent;
        this->array = REALLOC(this->array, this->extent);
    }
    this->array[this->size++] = s;
}

static void debug(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    GList* this = THIS(GList, "GList.debug");
    __(this).debug(fmt, args);
    printf(".list_array: %p\n", this->array);
    printf(".list_extent: %d\n", this->extent);
    printf(".list_size: %d\n", this->size);
    printf(".list_mult: %f\n", this->mult);
    // __(this).debug(".list_array: %p\n", this->array);
    // __(this).debug(".list_extent: %d\n", this->extent);
    // __(this).debug(".list_size: %d\n", this->size);
    // __(this).debug(".list_mult: %f\n", this->mult);
    for (int i = 0; i < this->size; i++) {
        printf("... %d %p\n", i, _(this).get(i));
    }
}

static void delete() {
    GList* this = THIS(GList, "GList.delete");
    free(this->array);
    __(this).delete();
}

GListClass GList$;
static void _initClass() {
    memcpy(&GList$, &GObj$, sizeof(GObj$));
    GList$.name = "GList";
    GList$.id = GList_ID;
    GList$.super = &GObj$;
    GList$.init = init;
    GList$.delete = delete;
    GList$.debug = debug;
    GList$.push = push;
    GList$.get = get;
}
