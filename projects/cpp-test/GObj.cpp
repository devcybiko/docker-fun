#include <iostream>
#include "GObj.h"

using namespace std;

GObj::GObj(string name)
{
    this->name = name;
}

GObj::~GObj()
{
}

// basic class function to convert "name" to string
string GObj::toString()
{
    return this->name;
}

void GObj::debug(string message)
{
    cout << message << endl;
}