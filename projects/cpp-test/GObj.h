#ifndef __GOBJ__
#define __GOBJ__

// include the std namespace
#include <string>

class GObj
{
public:
    GObj(std::string name);
    ~GObj();
    void debug(std::string message);
    std::string toString();
    // members
    std::string name;
};

#endif // __GOBJ__
