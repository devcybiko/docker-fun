#define TRACE_ON

#include "GPVM.h"
#include "GPTask.h"

GPVM* GPVM_new(int memsize) {
    if (GPVM$.id == 0) _initClass();
    GPVM *this = NEW(GPVM);
TRACE("this=%p\n", this);
    this->class = &GPVM$;
TRACE("this->class=%p\n", this->class);
    _(this).init(GPVM_ID, memsize);
}

static void init(int id, int memsize)
{
TRACE("> GPVM.init\n");
    GPVM* this = _THIS_; // special case for init
TRACE("this=%p\n", this);
    __(this).init(id);
    this->memory = GByteArray_new(round4(memsize));
TRACE("this->memory=%p\n", this->memory);
    this->taskList = GList_new();
TRACE("this->taskList=%p\n", this->taskList);
TRACE("< GPVM.init\n");
}

static void delete()
{
TRACE("> GPVM.delete\n");
    GPVM* this = THIS(GPVM, "GPVM.delete");
TRACE("this=%p\n", this);
    __(this).delete();
TRACE("< GPVM.delete\n");
}

static void debug(char* fmt, ...)
{
TRACE("> GPVM.debug\n");
    va_list args;
    va_start(args, fmt);
    GPVM* this = THIS(GPVM, "GPVM.debug");
TRACE("this=%p\n", this);
    __(this).debug(fmt, args);
TRACE("< GPVM.debug\n");
}

static int addTask(GPTask *task) {
TRACE("> GPVM.addTask\n");
    GPVM* this = THIS(GPVM, "GPVM.addTask");
TRACE("this=%p\n", this);
    _(this->taskList).push(task);
    task->taskID = this->taskList->size; // taskID is nonzero, one greater than index
TRACE("task->taskID=%p\n", task->taskID);
TRACE("< GPVM.addTask\n");
}

static char *allocMem(int memsize) {
TRACE("> GPVM.allocMem\n");
    GPVM* this = THIS(GPVM, "GPVM.allocMem");
TRACE("this=%p\n", this);
    char *memptr = _(this->memory).alloc(round4(memsize));
TRACE("memptr=%p\n", memptr);
TRACE("< GPVM.allocMem\n");
}

static int pump(void) {
TRACE("> GPVM.pump\n");
    GPVM* this = THIS(GPVM, "GPVM.pump");
TRACE("this=%p\n", this);
    for(int i=0; i<this->taskList->size; i++) {
        GPTask *task = this->taskList->array[i];
TRACE("task=%p\n", task);
        _(task).exec(1);
    }
TRACE("< GPVM.pump\n");
}

GPVMClass GPVM$;
static void _initClass() {
TRACE("> GPVM._initClass\n");
    memcpy(&GPVM$, &GObj$, sizeof(GObj$));
    GPVM$.name = "GPVM";
    GPVM$.id = GPVM_ID;
    GPVM$.super = &GObj$;
    GPVM$.init = init;
    GPVM$.delete = delete;
    GPVM$.debug = debug;
    GPVM$.addTask = addTask;
    GPVM$.allocMem = allocMem;
    GPVM$.pump = pump;
TRACE("< GPVM._initClass\n");
}
