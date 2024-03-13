#define TRACE_ON

#include "GByteArray.h"

GByteArray* GByteArray_new(int extent)
{
    if (GByteArray$.id == 0) _initClass();
    GByteArray* this = NEW(GByteArray);
TRACE("this=%p\n", this);
    this->class = &GByteArray$;
TRACE("this->class=%p\n", this->class);
    _(this).init(GByteArray_ID, extent);
}

static void init(int id, int extent)
{
TRACE("> GByteArray.init\n");
    GByteArray* this = _THIS_; // special case for init
TRACE("this=%p\n", this);
    __(this).init(id);
    this->used = 0;
TRACE("this->used=%p\n", this->used);
    this->extent = extent;
TRACE("this->extent=%p\n", this->extent);
    this->bytes = CALLOC(extent, char);
TRACE("this->bytes=%p\n", this->bytes);
TRACE("< GByteArray.init\n");
}

static void delete()
{
TRACE("> GByteArray.delete\n");
    GByteArray* this = THIS(GByteArray, "GByteArray.delete");
TRACE("this=%p\n", this);
    FREE(this->bytes);
    __(this).delete();
TRACE("< GByteArray.delete\n");
}

static void debug(char* fmt, ...)
{
TRACE("> GByteArray.debug\n");
    va_list args;
    va_start(args, fmt);
    GByteArray* this = THIS(GByteArray, "GByteArray.debug");
TRACE("this=%p\n", this);
    __(this).debug(fmt, args);
TRACE("< GByteArray.debug\n");
}

static char* alloc(int n) {
TRACE("> GByteArray.debug\n");
    GByteArray* this = THIS(GByteArray, "GByteArray.alloc");
TRACE("this=%p\n", this);
    if (n < 0 || this->used + n >= this->extent) return NULL;
    char* s = &this->bytes[this->used];
TRACE("s=%p\n", s);
    this->used += n;
TRACE("this->used=%p\n", this->used);
TRACE("< GByteArray.debug\n");
}

GByteArrayClass GByteArray$;
static void _initClass() {
TRACE("> GByteArray._initClass\n");
    memcpy(&GByteArray$, &GObj$, sizeof(GObj$));
    GByteArray$.name = "GByteArray";
    GByteArray$.id = GByteArray_ID;
    GByteArray$.super = &GObj$;
    GByteArray$.init = init;
    GByteArray$.delete = delete;
    GByteArray$.debug = debug;
    GByteArray$.alloc = alloc;
TRACE("< GByteArray._initClass\n");
}
