#include <stdio.h>
#include <stdlib.h>
#include "GObj.h"
#include "GList.h"
#include "GMap.h"
#include "GCron.h"
// #include "config.h"

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
    printf("Hello, World!\n");
    GObj *obj = GObj$->new("test");
    _(obj)->debug("GObj Test");
    printf("%s\n", _(obj)->toString());
    _(obj)->delete(0);

    GList *list = GList$->new("list", 0, 0.0);
    _(list)->push("zero");
    _(list)->push("one");
    _(list)->push("two");
    _(list)->debug("GList Test");
    printf("%s\n", (char *)_(list)->get(0));
    printf("", (char *)_(list)->get(1));
    printf("", (char *)_(list)->get(2));
    _(list)->delete();
    printf("\n");

    GMap *map = GMap$->new("map");
    _(map)->put("zero", "cero");
    _(map)->put("one", "uno");
    _(map)->put("two", "dos");
    _(map)->debug("GMap Test");
    printf("%s\n", (char *)_(map)->get("zero"));
    printf("%s\n", (char *)_(map)->get("one"));
    printf("%s\n", (char *)_(map)->get("two"));
    _(map)->delete();
    printf("\n");

    GCron *cron = GCron$->new("cron");
    _(cron)
        ->add("fast", 250, cronPrint, newContext("FAST!", 10))
        ->add("medium", 500, cronPrint, newContext("MEDIUM!", 10))
        ->add("slow", 1000, cronPrint, newContext("SLOW!", 10))
    ;

    for (
        int processed = _(cron)->pump();
        processed > 0;
        processed = _(cron)->pump()
    );
    return 0;
}