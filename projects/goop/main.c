#define TRACE_OFF

#include "GObj.h"
#include "GList.h"
#include "GMap.h"

int main(int argc, char const *argv[])
{
    printf("Hello, World!\n");
    GObj *obj = GObj_new();
    _(obj).debug("GObj Test");
    printf("%s\n", _(obj).toString());
    _(obj).delete();

    GList *list = GList_new();
    _(list).push("zero");
    _(list).push("one");
    _(list).push("two");
    _(list).debug("GList Test");
    printf("%s\n", (char *)_(list).get(0));
    printf("%s\n", (char *)_(list).get(1));
    printf("%s\n", (char *)_(list).get(2));
    _(list).delete();
    printf("\n");

    GMap *map = GMap_new();
    _(map).put("zero", "cero");
    _(map).put("one", "uno");
    _(map).put("two", "dos");
    _(map).debug("GMap Test");
    printf("%s\n", (char *)_(map).get("zero"));
    printf("%s\n", (char *)_(map).get("one"));
    printf("%s\n", (char *)_(map).get("two"));
    _(map).delete();
    printf("\n");

    return 0;
}