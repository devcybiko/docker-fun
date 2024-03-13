#define TRACE_ON

#include "GPTask.h"

GPTask* GPTask_new(GPVM* vm, int nCode, int nStatics, int nHeap) // nCode, nStatics, nHeap are nBytes
{
    TRACE("> GPTask.new\n");
    if (GPTask$.id == 0) _initClass();
    GPTask* this = NEW(GPTask);
TRACE("this=%p\n", this);
    TRACE("this = %p\n", this);
    this->class = &GPTask$;
TRACE("this->class=%p\n", this->class);
    _(this).init(GPTask_ID, vm, nCode, nStatics, nHeap);
    TRACE("< GPTask.new %p\n", this);
}

static void init(int id, GPVM* vm, int nCode, int nStatics, int nHeap) // nCode, nStatics, nHeap are nBytes
{
TRACE("> GPTask.init\n");
    GPTask* this = _THIS_; // special case for init
TRACE("this=%p\n", this);
    TRACE("> GPTask.init %p\n", this);
    __(this).init(id);
    nCode = round4(nCode);
TRACE("nCode=%p\n", nCode);
    nStatics = round4(nStatics);
TRACE("nStatics=%p\n", nStatics);
    nHeap = round4(nHeap);
TRACE("nHeap=%p\n", nHeap);
    int size = nCode + nStatics + nHeap;
TRACE("size=%p\n", size);
    char* mem = _(vm).allocMem(size);
TRACE("mem=%p\n", mem);
    this->code = (GP_WORD*)mem; // code is array of 16 bit words
TRACE("this->code=%p\n", this->code);
    this->statics = (GP_WORD*)&mem[nCode];
TRACE("this->statics=%p\n", this->statics);
    this->pc = 0;
TRACE("this->pc=%p\n", this->pc);
    this->sp = nCode + nStatics;
TRACE("this->sp=%p\n", this->sp);
    this->hp = size;
TRACE("this->hp=%p\n", this->hp);
    TRACE("< GPTask.init %p\n", this);
TRACE("< GPTask.init\n");
}

static void delete()
{
TRACE("> GPTask.delete\n");
    GPTask* this = THIS(GPTask, "GPTask.delete");
TRACE("this=%p\n", this);
    TRACE("> GPTask.delete %p\n", this);
    __(this).delete();
    TRACE("< GPTask.delete %p\n", this);
TRACE("< GPTask.delete\n");
}

static void debug(char* fmt, ...)
{
TRACE("> GPTask.debug\n");
    va_list args;
    va_start(args, fmt);
    GPTask* this = THIS(GPTask, "GPTask.debug");
TRACE("this=%p\n", this);
    TRACE("> GPTask.debug %p\n", this);
    __(this).debug(fmt, args);
    TRACE("< GPTask.debug %p\n", this);
TRACE("< GPTask.debug\n");
}

static int exec1(GPTask* this) {
TRACE("> GPTask.exec1\n");
    int op1, op2, result;
    GP_WORD opcode = this->code[this->pc++];
TRACE("opcode=%p\n", opcode);
    TRACE("OPCODE: 0x%04x\n", opcode);
    int hi = opcode >> 8;
TRACE("hi=%p\n", hi);
    int lo = opcode & 0xff;
TRACE("lo=%p\n", lo);
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
TRACE("op1=%p\n", op1);
        TRACE("unary op1=%d\n", op1);
        break;
    }
    case GP_BINARY_OPERATION: {
        // binary ops
        op2 = this->code[this->sp--];
TRACE("op2=%p\n", op2);
        op1 = this->code[this->sp--];
TRACE("op1=%p\n", op1);
        TRACE("binary op1=%d op2=%d\n", op1, op2);
        break;
    }
    }
    switch (lo) {
    case GP_NOP: TRACE("NOP\n"); break;
    case GP_ADD: {
        result = op1 + op2;
TRACE("result=%p\n", result);
        this->code[++this->sp] = result;
        TRACE("ADD %d + %d = %d\n", op1, op2, result);
        break;
    }
    case GP_SUB: {
        result = op1 - op2;
TRACE("result=%p\n", result);
        this->code[++this->sp] = result;
        TRACE("SUB %d - %d = %d\n", op1, op2, result);
        break;
    }
    case GP_MUL: {
        result = op1 * op2;
TRACE("result=%p\n", result);
        this->code[++this->sp] = result;
        TRACE("MUL %d * %d = %d\n", op1, op2, result);
        break;
    }
    case GP_DIV: {
        result = op1 / op2;
TRACE("result=%p\n", result);
        this->code[++this->sp] = result;
        TRACE("DIV %d / %d = %d\n", op1, op2, result);
        break;
    }
    case GP_MOD: {
        result = op1 % op2;
TRACE("result=%p\n", result);
        this->code[++this->sp] = result;
        TRACE("MOD %d %% %d = %d\n", op1, op2, result);
        break;
    }
    }
TRACE("< GPTask.exec1\n");
}

static int exec(int nInstructions)
{
TRACE("> GPTask.exec\n");
    GPTask* this = THIS(GPTask, "GPTask.exec");
TRACE("this=%p\n", this);
    TRACE("> GPTask.exec %p nInstructions=%d\n", this, nInstructions);
    for (int i = 0; i < nInstructions; i++) {
        exec1(this);
    }
    TRACE("< GPTask.exec %p\n", this);
TRACE("< GPTask.exec\n");
}

static void push(int n)
{
TRACE("> GPTask.push\n");
    GPTask* this = THIS(GPTask, "GPTask.push");
TRACE("this=%p\n", this);
    TRACE("> GPTask.push %p n=%d\n", this, n);
    this->code[++this->sp] = n;
    TRACE("< GPTask.push %p n=%d\n", this, n);
TRACE("< GPTask.push\n");
}

static int pop()
{
TRACE("> GPTask.pop\n");
    GPTask* this = THIS(GPTask, "GPTask.pop");
TRACE("this=%p\n", this);
    TRACE("> GPTask.pop %p\n", this);
    int n = this->code[this->sp--];
TRACE("n=%p\n", n);
    TRACE("< GPTask.pop %p n=%d\n", this, n);
TRACE("< GPTask.pop\n");
}

static int peek()
{
TRACE("> GPTask.peek\n");
    GPTask* this = THIS(GPTask, "GPTask.peek");
TRACE("this=%p\n", this);
    TRACE("> GPTask.peek %p\n", this);
    int n = this->code[this->sp];
TRACE("n=%p\n", n);
    TRACE("< GPTask.peek %p n=%d\n", this, n);
TRACE("< GPTask.peek\n");
}

GPTaskClass GPTask$;
static void _initClass() {
TRACE("> GPTask._initClass\n");
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
TRACE("< GPTask._initClass\n");
}