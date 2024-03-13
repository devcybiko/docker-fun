#ifndef __GPVM__
#define __GPVM__

#include "./gtos/GObj.h"
#include "./gtos/GList.h"
#include "utils.h"
#include "GByteArray.h"

typedef uint16_t GP_WORD;

typedef struct GPTask GPTask;

// echo -n "GPVM" | xxd -ps
#define GPVM_ID 0x4750564d

#define GPVM_MEMBERS(Obj, SuperObj) \
    GByteArray *memory;\
    GList *taskList;

#define GPVM_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id, int memsize);

#define GPVM_METHODS(Obj, SuperObj) \
    METHOD(char *, allocMem)(int memsize); \
    METHOD(int, addTask)(GPTask *task);\
    METHOD(int, pump)(void);

CLASS(GPVM, GObj)

extern GPVM* GPVM_new(int memsize);

#endif // __GPVM__
