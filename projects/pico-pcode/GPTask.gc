#define TRACE_OFF

#include "GPTask.h"

GPTask* GPTask_new(GPVM* vm, int nCode, int nStatics, int nHeap) // nCode, nStatics, nHeap are nBytes
{
    if (GPTask$.id == 0) _initClass();
    GPTask* this = NEW(GPTask);
    this->class = &GPTask$;
    _(this).init(GPTask_ID, vm, nCode, nStatics, nHeap);
    return this;
}

static void init(int id, GPVM* vm, int nCode, int nStatics, int nHeap) // nCode, nStatics, nHeap are nBytes
{
    GPTask* this = _THIS_; // special case for init
    __(this).init(id);
    nCode = round4(nCode);
    nStatics = round4(nStatics);
    nHeap = round4(nHeap);
    int size = nCode + nStatics + nHeap;
    char* mem = _(vm).allocMem(size);
    this->code = (GP_WORD*)mem; // code is array of 16 bit words
    this->statics = (GP_WORD*)&mem[nCode];
    this->pc = 0;
    this->sp = nCode + nStatics;
    this->hp = size;
}

static void delete()
{
    GPTask* this = THIS(GPTask, "GPTask.delete");
    __(this).delete();
}

static void debug(char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    GPTask* this = THIS(GPTask, "GPTask.debug");
    __(this).debug(fmt, args);
}

static int exec1(GPTask* this) {
    int op1, op2, result;
    GP_WORD opcode = this->code[this->pc++];
    int hi = opcode >> 8;
    int lo = opcode & 0xff;

    if (opcode == 0xffff) {
        this->pc--;
            return -1;
    }
    switch (hi) {
    case 0: {
        // basic codes
        break;
    }
    case GP_UNARY_OPERATION: {
        // unary ops
        op1 = this->code[this->sp--];
            break;
    }
    case GP_BINARY_OPERATION: {
        // binary ops
        op2 = this->code[this->sp--];
        op1 = this->code[this->sp--];
            break;
    }
    }
    switch (lo) {
    case GP_NOP: TRACE("NOP\n"); break;
    case GP_ADD: {
        result = op1 + op2;
        this->code[++this->sp] = result;
            break;
    }
    case GP_SUB: {
        result = op1 - op2;
        this->code[++this->sp] = result;
            break;
    }
    case GP_MUL: {
        result = op1 * op2;
        this->code[++this->sp] = result;
            break;
    }
    case GP_DIV: {
        result = op1 / op2;
        this->code[++this->sp] = result;
            break;
    }
    case GP_MOD: {
        result = op1 % op2;
        this->code[++this->sp] = result;
            break;
    }
    }
    return 0;
}

static int exec(int nInstructions)
{
    GPTask* this = THIS(GPTask, "GPTask.exec");
    for (int i = 0; i < nInstructions; i++) {
        exec1(this);
    }
}

static void push(int n)
{
    GPTask* this = THIS(GPTask, "GPTask.push");
    this->code[++this->sp] = n;
}

static int pop()
{
    GPTask* this = THIS(GPTask, "GPTask.pop");
    int n = this->code[this->sp--];
    return n;
}

static int peek()
{
    GPTask* this = THIS(GPTask, "GPTask.peek");
    int n = this->code[this->sp];
    return n;
}

GPTaskClass GPTask$;
static void _initClass() {
    memcpy(&GPTask$, &GObj$, sizeof(GObj$));
    GPTask$.name = "GPTask";
    GPTask$.id = GPTask_ID;
    GPTask$.super = &GObj$;
    GPTask$.init = init;
    GPTask$.delete = delete;
    GPTask$.debug = debug;
    GPTask$.exec = exec;
    GPTask$.push = push;
    GPTask$.pop = pop;
    GPTask$.peek = peek;
}
