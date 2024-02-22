#ifndef __Timer__
#define __Timer__

#include <stdint.h>

typedef struct  {
    uint64_t (*uSecs)();
    uint32_t (*mSecs)();
} GTimerClass;

extern GTimerClass *GTIMER;

#endif // __Timer__
