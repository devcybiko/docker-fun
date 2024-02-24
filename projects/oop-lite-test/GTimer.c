#include "GTimer.h"

#ifdef PICO
#include "pico/GTimer.c"
#else // linux?
#include "linux/GTimer.c"
#endif

static GTimerClass _GTIMER = {
    .uSecs = uSecs,
    .mSecs = mSecs,
};

GTimerClass *GTIMER = &_GTIMER;