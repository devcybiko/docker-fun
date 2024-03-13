#define TRACE_OFF

#include "GByteArray.h"

GByteArray* GByteArray_new(int extent)
{
    if (GByteArray$.id == 0) _initClass();
    GByteArray* this = NEW(GByteArray);
    this->class = &GByteArray$;
    _(this).init(GByteArray_ID, extent);
    return this;
}

static void init(int id, int extent)
{
    GByteArray* this = _THIS_; // special case for init
    __(this).init(id);
    this->used = 0;
    this->extent = extent;
    this->bytes = CALLOC(extent, char);
}

static void delete()
{
    GByteArray* this = THIS(GByteArray, "GByteArray.delete");
    FREE(this->bytes);
    __(this).delete();
}

static void debug(char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    GByteArray* this = THIS(GByteArray, "GByteArray.debug");
    __(this).debug(fmt, args);
}

static char* alloc(int n) {
    GByteArray* this = THIS(GByteArray, "GByteArray.alloc");
    if (n < 0 || this->used + n >= this->extent) return NULL;
    char* s = &this->bytes[this->used];
    this->used += n;
    return s;
}

GByteArrayClass GByteArray$;
static void _initClass() {
    memcpy(&GByteArray$, &GObj$, sizeof(GObj$));
    GByteArray$.name = "GByteArray";
    GByteArray$.id = GByteArray_ID;
    GByteArray$.super = &GObj$;
    GByteArray$.init = init;
    GByteArray$.delete = delete;
    GByteArray$.debug = debug;
    GByteArray$.alloc = alloc;
}
