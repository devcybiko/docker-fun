#ifndef __GList__
#define __GList__

#include "GObj.h"

// create a new C++ class GList that inherits from GObj and has members array, extent, size, and mult
class GList : public GObj
{
public:
    void **array;
    int extent;
    int size;
    double mult;

    GList(std::string name, int extent, double mult);
    ~GList();
    void debug(std::string message);
    std::string toString();

    GList *push(void *value);
    void *get(int n);
};

#endif // __GList__
