#ifndef __GPTask__
#define __GPTask__

#include "./gtos/GObj.h"
#include "./gtos/GList.h"
#include "GPVM.h"

// echo -n "Task" | xxd -ps
#define GPTask_ID 0x5461736b

#define GP_OPCODE(hi,lo) ((hi<<8)+lo)
#define GP_NOP 0x0000

// unary operations
#define GP_UNARY_OPERATION 0x01
#define GP_ABS 0x01
#define GP_NEG 0x02

// binary operations
#define GP_BINARY_OPERATION 2
#define GP_ADD 0x01
#define GP_SUB 0x02
#define GP_MUL 0x03
#define GP_DIV 0x04
#define GP_MOD 0x05

#define GP_STOP 0xffff

#define GPTask_MEMBERS(Obj, SuperObj) \
    int taskID;\
    GP_WORD *code;\
    GP_WORD *statics;\
    int sp;\
    int hp;\
    int pc;\

#define GPTask_CONSTRUCTOR(Obj, SuperObj) \
    METHOD(void, init)(int id, GPVM *vm, int nCode, int nStatics, int nHeap);

#define GPTask_METHODS(Obj, SuperObj) \
    METHOD(int, exec)(int nInstructions); \
    METHOD(void, push)(int n); \
    METHOD(int, pop)(); \
    METHOD(int, peek)(); \

CLASS(GPTask, GObj)

extern GPTask* GPTask_new(GPVM *vm, int nCode, int nStatics, int nHeap);

#endif // __GPTask__
