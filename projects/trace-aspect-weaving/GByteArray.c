#include "GByteArray.h"

GByteArray* GByteArray_new(int extent)
{
    TRACE("> GByteArray_new");
    if (GByteArray$.id == 0) _initClass();
    GByteArray* this = NEW(GByteArray);
    TRACE("this=%p", this);
    this->class = &GByteArray$;
    TRACE("this->class=%p", this->class);
    _(this).init(GByteArray_ID, extent);
    TRACE("< GByteArray_new");
}

static void init(int id, int extent)
{
    TRACE("> init");
    GByteArray* this = _THIS_; // special case for init
    TRACE("this=%p", this);
    __(this).init(id);
    this->used = 0;
    TRACE("this->used=%p", this->used);
    this->extent = extent;
    TRACE("this->extent=%p", this->extent);
    this->bytes = CALLOC(extent, char);
    TRACE("this->bytes=%p", this->bytes);
    TRACE("< init");
}

static void delete()
{
    TRACE("> delete");
    GByteArray* this = THIS(GByteArray, "GByteArray.delete");
    TRACE("this=%p", this);
    FREE(this->bytes);
    __(this).delete();
    TRACE("< delete");
}

static void debug(char* fmt, ...)
{
    TRACE("> debug");
    va_list args;
    va_start(args, fmt);
    GByteArray* this = THIS(GByteArray, "GByteArray.debug");
    TRACE("this=%p", this);
    __(this).debug(fmt, args);
    TRACE("< debug");
}

static char* alloc(int n) {
    TRACE("> alloc");
    GByteArray* this = THIS(GByteArray, "GByteArray.alloc");
    TRACE("this=%p", this);
    if (n < 0 || this->used + n >= this->extent) return NULL;
    char* s = &this->bytes[this->used];
    TRACE("s=%p", s);
    this->used += n;
    TRACE("this->used=%p", this->used);
    TRACE("< alloc");
}

GByteArrayClass GByteArray$;
static void _initClass() {
    TRACE("> _initClass");
    memcpy(&GByteArray$, &GObj$, sizeof(GObj$));
    GByteArray$.name = "GByteArray";
    GByteArray$.id = GByteArray_ID;
    GByteArray$.super = &GObj$;
    GByteArray$.init = init;
    GByteArray$.delete = delete;
    GByteArray$.debug = debug;
    GByteArray$.alloc = alloc;
    TRACE("< _initClass");
}
