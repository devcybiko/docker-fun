#include "GObj.h"
#include "GList.h"
#include "GMap.h"
#include "GCron.h"

typedef struct Context {
    char *message;
    int counter;
} Context;

void * newContext(char *message, int counter)
{
    Context *context = (Context *)malloc(sizeof(Context));
    context->message = message;
    context->counter = counter;
    return context;
}

int cronPrint(GCronEntry *entry)
{
    Context *context = (Context *)entry->context;
    context->counter--;
    cout << "cronPrint: " << entry->name << ", " << context->message << ", " << context->counter << endl;
    if (context->counter == 0)
    {
        cout << endl << context->message << " deactivated" << endl << endl;
        return GCRON_DEACTIVATED;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    cout << "Hello, World!" << endl;
    GObj *obj = new GObj("test");
    obj->debug("GObj Test");
    cout << obj->toString() << endl;
    delete obj;
    cout << endl;

    GList *list = new GList("list", 0, 0.0);
    list->push("zero");
    list->push("one");
    list->push("two");
    list->debug("GList Test");
    cout << (char *)list->get(0) << endl;
    cout << (char *)list->get(1) << endl;
    cout << (char *)list->get(2) << endl;
    delete list;
    cout << endl;

    GMap *map = new GMap("map");
    map->put("zero", "cero");
    map->put("one", "uno");
    map->put("two", "dos");
    map->debug("GMap Test");
    cout << (char *)map->get("zero") << endl;
    cout << (char *)map->get("one") << endl;
    cout << (char *)map->get("two") << endl;
    delete map;
    cout << endl;

    GCron *cron = new GCron("cron");
    cron
        ->add("fast", 250, cronPrint, newContext("FAST!", 10))
        ->add("medium", 500, cronPrint, newContext("MEDIUM!", 10))
        ->add("slow", 1000, cronPrint, newContext("SLOW!", 10))
    ;

    for (
        int processed = cron->pump();
        processed > 0;
        processed = cron->pump()
    );
    return 0;
}