#include <iostream>

#include "GObj.h"
#include "GList.h"

using namespace std;

int main(int argc, char const *argv[])
{
    GObj *gobj = new GObj("test");
    cout << gobj->toString() << endl;
    delete gobj;
    GList *list = new GList("list", 0, 0.0);
    list->push((void *)1);
    list->push((void *)2);
    cout << list->get(0) << endl;
    return 0;
}