#define TRACE_OFF

#include "GPCode.h"

GPCode *GPCode_new(void)
{
    TRACE("> GPCode.new\n");
    if (GPCode$.id == 0)
        _initClass();
    GPCode *this = NEW(GPCode);
    TRACE("this = %p\n", this);
    this->class = &GPCode$;
    _(this).init(GPCode_ID);
    TRACE("< GPCode.new %p\n", this);
    return this;
}

static void init(int id)
{
    GPCode *this = _THIS_; // special case for init
    TRACE("> GPCode.init %p\n", this);
    __(this).init(id);
    TRACE("< GPCode.init %p\n", this);
}

static void delete()
{
    GPCode *this = THIS(GPCode, "GPCode.delete");
    TRACE("> GPCode.delete %p\n", this);
    __(this).delete();
    TRACE("< GPCode.delete %p\n", this);
}

static void debug(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    GPCode *this = THIS(GPCode, "GPCode.debug");
    TRACE("> GPCode.debug %p\n", this);
    __(this).debug(fmt, args);
    TRACE("< GPCode.debug %p\n", this);
}

static void* get(int n) {
    GPCode* this = THIS(GPCode, "GPCode.toString");
    TRACE("> GPCode.get %p n=%d\n", this, n);
    if (n < 0 || n >= this->size)
        return NULL;
    void* s = this->array[n];
    TRACE("< GPCode.get %p n=%d\n", this, n);
    _(this);
    return s;
}

static void push(void* s) {
    GPCode* this = THIS(GPCode, "GPCode.push");
    TRACE("> GPCode.push %p s=%p\n", this, s);
    TRACE("array=%p size=%d, extent=%d\n", this->array, this->size, this->extent);
    if (this->size == this->extent) {
        int new_extent = this->extent * this->mult;
        TRACE("... List Extent ... %d -> %d\n", this->extent, new_extent);
        this->extent = new_extent;
        this->array = REALLOC(this->array, this->extent);
    }
    this->array[this->size++] = s;
    TRACE("< GPCode.push %p s=%p\n", this, s);
}

GPCodeClass GPCode$;
static void _initClass() {
    TRACE("> GPCode$._initClass\n");
    memcpy(&GPCode$, &GObj$, sizeof(GObj$));
    GPCode$.name = "GPCode";
    GPCode$.id = GPCode_ID;
    GPCode$.super = &GObj$;
    GPCode$.init = init;
    GPCode$.delete = delete;
    GPCode$.debug = debug;
    GPCode$.push = push;
    GPCode$.get = get;
    TRACE("< GPCode$._initClass\n");
}