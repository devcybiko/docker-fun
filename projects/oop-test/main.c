/*
 * gtos for Raspberry Pi Pico
 *
 * @version     1.0.0
 * @author      <YOU>
 * @copyright   2024
 * @licence     MIT
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "GList.h"
#include "GCron.h"
#include "GMap.h"
#include "config.h"

 // testprogram
GMap *gconfig;

int fast_counter = 0;
int blinky(GCronEntry* obj) {
    printf("%s\n", (char *) _(gconfig)->get((char *)obj->context));
    return 0;
}

int main() {
    // Use for debugging
    // stdio_init_all();
    gconfig = GMap$->new("config");
    _(gconfig)->putEntries(config);
    GCron *cron = GCron$->new("crontab");
    _(cron)->debug("crontab")->add("fast", 250, blinky, "key1");
    _(cron)->debug("crontab")->add("\nmedium\n", 1000, blinky, (void *)"key2");
    _(cron)->debug("crontab")->add("\nslow\n", 2000, blinky, (void *)"key3");

    while (true) {
        cron->class->pump();
    }
    return 0;
}
