#include "GObj.h"
#include "GList.h"
// #include "GMap.h"
// #include "GCron.h"

// typedef struct Context {
//     char *message;
//     int counter;
// } Context;

// void * newContext(char *message, int counter)
// {
//     Context *context = (Context *)malloc(sizeof(Context));
//     context->message = message;
//     context->counter = counter;
//     return context;
// }

// int cronPrint(GCronEntry *entry)
// {
//     Context *context = (Context *)entry->context;
//     context->counter--;
//     printf("%s\n", "cronPrint: " << entry->name << ", " << context->message << ", " << context->counter);
//     if (context->counter == 0)
//     {
//         printf("%s\n", endl << context->message << " deactivated"));
//         return GCRON_DEACTIVATED;
//     }
//     return 0;
// }

int main(int argc, char const *argv[])
{
    printf("\n%s\n", "Hello, World!\n");

    printf("%s\n", "Begin GObj Test...");
    GObj *obj = GObj_new("test");
    _(obj)->debug("GObj Test");
    printf("%s\n", obj->toString());
    _(obj)->delete();
    printf("GObj Test Done\n");

    printf("\n%s\n", "Begin GList Test!\n");
    GList *list = GList_new("list", 0, 0.0);
    printf("%p\n", list);
    printf("%p\n", list->toString);
    printf("%s\n", _(list)->toString());
    // list->push("zero");
    // list->push("one");
    // list->push("two");
    // list->debug("GList Test");
    // printf("%s\n", (char *)list->get(0));
    // printf("%s\n", (char *)list->get(1));
    // printf("%s\n", (char *)list->get(2));
    // delete list;
    // printf("%s\n", endl;

    // GMap *map = new GMap("map");
    // map->put("zero", "cero");
    // map->put("one", "uno");
    // map->put("two", "dos");
    // map->debug("GMap Test");
    // printf("%s\n", (char *)map->get("zero"));
    // printf("%s\n", (char *)map->get("one"));
    // printf("%s\n", (char *)map->get("two"));
    // delete map;
    // printf("%s\n", endl;

    // GCron *cron = new GCron("cron");
    // cron
    //     ->add("fast", 250, cronPrint, newContext("FAST!", 10))
    //     ->add("medium", 500, cronPrint, newContext("MEDIUM!", 10))
    //     ->add("slow", 1000, cronPrint, newContext("SLOW!", 10))
    // ;

    // for (
    //     int processed = cron->pump();
    //     processed > 0;
    //     processed = cron->pump()
    // );
    return 0;
}