#include "GObj.h"
#include "GList.h"
#include "GMap.h"
#include "GCronEntry.h"
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
    printf("cronPrint: %s, %s, %d\n", entry->name, context->message, context->counter);
    if (context->counter == 0)
    {
        printf("\n%s deactivated\n\n", context->message);
        return GCRON_DEACTIVATED;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    printf("\n%s\n", "Hello, World!\n");

    printf("%s\n", "Begin GObj Test...");
    GObj *obj = GObj_new("test");
    _(obj).debug("GObj Test");
    printf("%s\n", _(obj).toString());
    // _(obj)->delete();
    printf("GObj Test Done\n");

    printf("\n%s\n", "Begin GList Test!\n");
    GList *list = GList_new("list", 0, 0.0);
    printf("%p\n", list);
    printf("%p\n", _(list).toString);
    printf("%s\n", _(list).toString());
    _(list).push("zero");
    _(list).push("one");
    _(list).push("two");
    _(list).debug("GList Test");
    printf("%s\n", (char *)_(list).get(0));
    printf("%s\n", (char *)_(list).get(1));
    printf("%s\n", (char *)_(list).get(2));
    _(list).delete();
    printf("GList Test Done\n");

    printf("\n%s\n", "Begin GMap Test!\n");
    GMap *map = GMap_new("map");
    _(map).put("zero", "cero");
    _(map).put("one", "uno");
    _(map).put("two", "dos");
    _(map).debug("GMap Test");
    printf("%s\n", (char *)_(map).get("zero"));
    printf("%s\n", (char *)_(map).get("one"));
    printf("%s\n", (char *)_(map).get("two"));
    _(map).delete();
    printf("GMap Test Done\n");

    printf("\n%s\n", "Begin GCronEntry Test!\n");
    GCronEntry *entry = GCronEntry_new("entry", 100, NULL, NULL);
    _(entry).debug("GCronEntry Test");

    printf("\n%s\n", "Begin GCron Test!\n");
    GCron *cron = GCron_new("cron");
    _(cron).debug("GCron Test");
    _(cron).add("fast", 250, cronPrint, newContext("FAST!", 10));
    _(cron).add("medium", 500, cronPrint, newContext("MEDIUM!", 10));
    _(cron).add("slow", 1000, cronPrint, newContext("SLOW!", 10));

    for (
        int processed = _(cron).pump();
        processed > 0;
        processed = _(cron).pump()
    );
    return 0;
}