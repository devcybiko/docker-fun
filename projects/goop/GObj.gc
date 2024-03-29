#include "GObj.h"

GObj* GObj_new(void)
{
    if (GObj$.id == 0) _initClass();
    GObj* this = NEW(GObj);
    this->class = &GObj$;
    _(this).init(GObj_ID);
    return this;
}

static void init(int id) {
    GObj* this = _THIS_; // special case for init
    this->id = id;
}

static void delete(void) {
    GObj* this = THIS(GObj, "GObj.delete");
    FREE(this);
}

static char buffer[256];
static char* format(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int n = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    return buffer;
}

static char* toString(void) {
    GObj* this = THIS(GObj, "GObj.toString");
    _THIS_ = this;
    char* s = format("%s: %p", this->class->name, this);
    return s;
}

static void debug(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    GObj* this = THIS(GObj, "GObj.debug");
    _THIS_ = this;
    char* s = format(fmt, args);
    // char *s = "GObj.toString: 0x12345678";
    printf("%s\n", s);
    va_end(args);
}

GObjClass GObj$;
static void _initClass() {
    GObj$.name = "GObj";
    GObj$.id = GObj_ID;
    GObj$.super = NULL;
    GObj$.init = init;
    GObj$.delete = delete;
    GObj$.toString = toString;
    GObj$.format = format;
    GObj$.debug = debug;
}
