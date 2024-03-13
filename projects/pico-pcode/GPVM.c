#define TRACE_OFF

#include "GPVM.h"
#include "GPTask.h"

GPVM* GPVM_new(int memsize) {
    if (GPVM$.id == 0) _initClass();
    GPVM *this = NEW(GPVM);
    this->class = &GPVM$;
    _(this).init(GPVM_ID, memsize);
    return this;
}

static void init(int id, int memsize)
{
    GPVM* this = _THIS_; // special case for init
    __(this).init(id);
    this->memory = GByteArray_new(round4(memsize));
    this->taskList = GList_new();
}

static void delete()
{
    GPVM* this = THIS(GPVM, "GPVM.delete");
    __(this).delete();
}

static void debug(char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    GPVM* this = THIS(GPVM, "GPVM.debug");
    __(this).debug(fmt, args);
}

static int addTask(GPTask *task) {
    GPVM* this = THIS(GPVM, "GPVM.addTask");
    _(this->taskList).push(task);
    task->taskID = this->taskList->size; // taskID is nonzero, one greater than index
    return task->taskID;
}

static char *allocMem(int memsize) {
    GPVM* this = THIS(GPVM, "GPVM.allocMem");
    char *memptr = _(this->memory).alloc(round4(memsize));
    return memptr;
}

static int pump(void) {
    GPVM* this = THIS(GPVM, "GPVM.pump");
    for(int i=0; i<this->taskList->size; i++) {
        GPTask *task = this->taskList->array[i];
        _(task).exec(1);
    }
    return 0;
}

GPVMClass GPVM$;
static void _initClass() {
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
}
