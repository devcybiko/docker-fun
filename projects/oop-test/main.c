#include "Object.h"
#include "List.h"
// #include "Node.h"

int main() {
    DEBUG("> main\n");
    ObjectClass *Object = getObjectClass();
    ObjectInstance *obj = Object->new("greg");
    Object->debug(obj, "wowsers");
    Object->destroy(obj);

    ListClass *List = getListClass();
    ListInstance *list = List->new("smith");
    List->debug(list, "list!");
    for(int i=0; i<1000; i++) {
        List->push(list, (void *) i);
    }
    // List->debug(list, "list!");
    
    // Node *node = newNode("smith", NULL);
    // node->_->debug(node, "node!");

    DEBUG("< main\n");
}
