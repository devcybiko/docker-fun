#ifndef __GObj__
#define __GObj__

// include the std namespace
#include <string>
#include <iostream>

using namespace std;

class GObj
{
public:
    std::string name;

    GObj(std::string name);
    ~GObj();
    void debug(std::string message);
    std::string toString();
};

#endif // __GObj__
