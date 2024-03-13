#define TRACE_OFF

#include "GPVM.h"
#include "GPTask.h"

GPVM* GPVM_new(int memsize) {
    TRACE("> GPVM.new memsize=%d\n");
    if (GPVM$.id == 0) _initClass();
    GPVM *this = NEW(GPVM);
    TRACE("this = %p\n", this);
    this->class = &GPVM$;
    _(this).init(GPVM_ID, memsize);
    TRACE("< GPVM.new %p\n", this);
    return this;
}

static void init(int id, int memsize)
{
    GPVM* this = _THIS_; // special case for init
    TRACE("> GPVM.init %p\n", this);
    __(this).init(id);
    this->memory = GByteArray_new(round4(memsize));
    this->taskList = GList_new();
    TRACE("< GPVM.init %p\n", this);
}

static void delete()
{
    GPVM* this = THIS(GPVM, "GPVM.delete");
    TRACE("> GPVM.delete %p\n", this);
    __(this).delete();
    TRACE("< GPVM.delete %p\n", this);
}

static void debug(char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    GPVM* this = THIS(GPVM, "GPVM.debug");
    TRACE("> GPVM.debug %p\n", this);
    __(this).debug(fmt, args);
    TRACE("< GPVM.debug %p\n", this);
}

static int addTask(GPTask *task) {
    GPVM* this = THIS(GPVM, "GPVM.addTask");
    TRACE("> GPVM.addTask this=%p task=%p\n", this, task);
    _(this->taskList).push(task);
    task->taskID = this->taskList->size; // taskID is nonzero, one greater than index
    TRACE("< GPVM.addTask this=%p task=%p taskID=task->taskID\n", this, task, task->taskID);
    return task->taskID;
}

static char *allocMem(int memsize) {
    GPVM* this = THIS(GPVM, "GPVM.allocMem");
    TRACE("> GPVM.allocMem this=%p memsize=%d\n", this, memsize);
    char *memptr = _(this->memory).alloc(round4(memsize));
    TRACE("< GPVM.allocMem this=%p memptr=%p\n", this, memptr);
    return memptr;
}

static int pump(void) {
    GPVM* this = THIS(GPVM, "GPVM.pump");
    TRACE("> GPVM.pump this=%p\n", this);
    for(int i=0; i<this->taskList->size; i++) {
        GPTask *task = this->taskList->array[i];
        _(task).exec(1);
    }
    TRACE("< GPVM.pump this=%p\n", this);
    return 0;
}

GPVMClass GPVM$;
static void _initClass() {
    TRACE("> GPVM$._initClass\n");
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
    TRACE("< GPVM$._initClass\n");
}
