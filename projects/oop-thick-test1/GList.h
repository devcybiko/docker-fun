#ifndef __GList__
#define __GList__

#include "GObj.h"

// create a new C++ class GList that inherits from GObj and has members array, extent, size, and mult
typedef struct GList GList;
typedef struct GList {
    // members
    char name[16];

    // methods
    GList *(*init)(char *name, int extent, double mult);
    GObj *(*delete)();
    void (*debug)(char *message);
    char *(*toString)();

    void **array;
    int extent;
    int size;
    double mult;

    // void debug(std::string message);
    // std::string toString();

    // GList *push(void *value);
    // void *get(int n);
} GList;

GList *GList_new(char *name, int extent, double mult);

#endif // __GList__