#include "Object.h"
#include "List.h"
// #include "Node.h"

int main() {
    DEBUG("> main\n");
    Object *obj = objectNew("greg");
    obj->debug(obj, "wowsers")->destroy(obj);

    List *list = listNew("smith", 10, 0);
    list->debug(list, "list!");
    for(int i=0; i<20; i++) {
        char s[100];
        sprintf(s, "%d", i);
        printf("%d, %s\n", i, s);
        list->push(list, strdup(s));
    }
    list->debug(list, "list!");
    
    // Node *node = newNode("smith", NULL);
    // node->_->debug(node, "node!");

    DEBUG("< main\n");
}
