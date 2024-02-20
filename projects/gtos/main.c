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
int blinky(GCron* obj) {
    printf("%s\n", (char *)GMAP->get(gconfig, (char *)obj->context));
    return 0;
}

int main() {
    // Use for debugging
    // stdio_init_all();
    gconfig = GMAP->new("config");
    GMAP->addMap(gconfig, config);

    GCRON->new("fast", 250, blinky, (void *)"key1");
    GCRON->new("\nmedium\n", 1000, blinky, (void *)"key2");
    GCRON->new("\nslow\n", 2000, blinky, (void *)"key3");

    while (true) {
        GCRON->pump();
    }
    return 0;
}
