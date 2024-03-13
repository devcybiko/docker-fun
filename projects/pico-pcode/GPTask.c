#define TRACE_OFF

#include "GPTask.h"

GPTask* GPTask_new(GPVM* vm, int nCode, int nStatics, int nHeap) // nCode, nStatics, nHeap are nBytes
{
    TRACE("> GPTask.new\n");
    if (GPTask$.id == 0) _initClass();
    GPTask* this = NEW(GPTask);
    TRACE("this = %p\n", this);
    this->class = &GPTask$;
    _(this).init(GPTask_ID, vm, nCode, nStatics, nHeap);
    TRACE("< GPTask.new %p\n", this);
    return this;
}

static void init(int id, GPVM* vm, int nCode, int nStatics, int nHeap) // nCode, nStatics, nHeap are nBytes
{
    GPTask* this = _THIS_; // special case for init
    TRACE("> GPTask.init %p\n", this);
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
    TRACE("< GPTask.init %p\n", this);
}

static void delete()
{
    GPTask* this = THIS(GPTask, "GPTask.delete");
    TRACE("> GPTask.delete %p\n", this);
    __(this).delete();
    TRACE("< GPTask.delete %p\n", this);
}

static void debug(char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    GPTask* this = THIS(GPTask, "GPTask.debug");
    TRACE("> GPTask.debug %p\n", this);
    __(this).debug(fmt, args);
    TRACE("< GPTask.debug %p\n", this);
}

static int exec1(GPTask* this) {
    int op1, op2, result;
    GP_WORD opcode = this->code[this->pc++];
    TRACE("OPCODE: 0x%04x\n", opcode);
    int hi = opcode >> 8;
    int lo = opcode & 0xff;
    TRACE("hi=%02x, lo=%02x\n", hi, lo);

    if (opcode == 0xffff) {
        this->pc--;
        TRACE("STOPPED taskID=%d\n", this->taskID);
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
        TRACE("unary op1=%d\n", op1);
        break;
    }
    case GP_BINARY_OPERATION: {
        // binary ops
        op2 = this->code[this->sp--];
        op1 = this->code[this->sp--];
        TRACE("binary op1=%d op2=%d\n", op1, op2);
        break;
    }
    }
    switch (lo) {
    case GP_NOP: TRACE("NOP\n"); break;
    case GP_ADD: {
        result = op1 + op2;
        this->code[++this->sp] = result;
        TRACE("ADD %d + %d = %d\n", op1, op2, result);
        break;
    }
    case GP_SUB: {
        result = op1 - op2;
        this->code[++this->sp] = result;
        TRACE("SUB %d - %d = %d\n", op1, op2, result);
        break;
    }
    case GP_MUL: {
        result = op1 * op2;
        this->code[++this->sp] = result;
        TRACE("MUL %d * %d = %d\n", op1, op2, result);
        break;
    }
    case GP_DIV: {
        result = op1 / op2;
        this->code[++this->sp] = result;
        TRACE("DIV %d / %d = %d\n", op1, op2, result);
        break;
    }
    case GP_MOD: {
        result = op1 % op2;
        this->code[++this->sp] = result;
        TRACE("MOD %d %% %d = %d\n", op1, op2, result);
        break;
    }
    }
    return 0;
}

static int exec(int nInstructions)
{
    GPTask* this = THIS(GPTask, "GPTask.exec");
    TRACE("> GPTask.exec %p nInstructions=%d\n", this, nInstructions);
    for (int i = 0; i < nInstructions; i++) {
        exec1(this);
    }
    TRACE("< GPTask.exec %p\n", this);
}

static void push(int n)
{
    GPTask* this = THIS(GPTask, "GPTask.push");
    TRACE("> GPTask.push %p n=%d\n", this, n);
    this->code[++this->sp] = n;
    TRACE("< GPTask.push %p n=%d\n", this, n);
}

static int pop()
{
    GPTask* this = THIS(GPTask, "GPTask.pop");
    TRACE("> GPTask.pop %p\n", this);
    int n = this->code[this->sp--];
    TRACE("< GPTask.pop %p n=%d\n", this, n);
    return n;
}

static int peek()
{
    GPTask* this = THIS(GPTask, "GPTask.peek");
    TRACE("> GPTask.peek %p\n", this);
    int n = this->code[this->sp];
    TRACE("< GPTask.peek %p n=%d\n", this, n);
    return n;
}

GPTaskClass GPTask$;
static void _initClass() {
    TRACE("> GPTask$._initClass\n");
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
    TRACE("< GPTask$._initClass\n");
}
