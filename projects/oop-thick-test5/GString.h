#ifndef __GString__
#define __GString__

#include "GObj.h"

// echo -n "GString" | xxd -ps
// 47537472696e67
#define GString_ID 0x47537472696e67

CLASS(GString)
    GObj_CLASS
    char *value;

    METHOD(char *, set)(char *message);
    METHOD(char *, get)();
    METHOD(bool, equals)(char *other);
CLASS_END(GString);

GString *GString_new_full(char *name, char *value);
GString *GString_new(char *value);

#endif // __GString__