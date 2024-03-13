#define TRACE_OFF

#include "main.h"
# include "GPVM.h"
#include "GPTask.h"

int assert(char* msg, int expected, int actual) {
    if (expected != actual) {
        printf("ASSERT ERROR: %s expected=%d actual=%d\n", msg, expected, actual);
        exit(1);
    }
}

int main(int argc, char const* argv[])
{
    printf("Hello, World!\n");
    GObj* obj = GObj_new();
    GPVM* vm = GPVM_new(1000);
    GPTask* task = GPTask_new(vm, 100, 100, 100);
    int taskID = _(vm).addTask(task);
    printf("TaskID=%d\n", taskID);
    assert("taskID", 1, taskID);

    int pc = 0;
    _(task).push(1);
    _(task).push(2);
    task->code[pc++] = GP_NOP;
    _(vm).pump();
    assert("NOP", 2, _(task).peek());

    task->code[pc++] = GP_OPCODE(GP_BINARY_OPERATION, GP_ADD);
    _(vm).pump();
    assert("ADD", 3, _(task).peek());

    task->code[pc++] = GP_OPCODE(GP_BINARY_OPERATION, GP_SUB);
    _(task).push(1);
    _(vm).pump();
    assert("SUB", 2, _(task).peek());

    task->code[pc++] = GP_OPCODE(GP_BINARY_OPERATION, GP_MUL);
    _(task).push(7);
    _(vm).pump();
    assert("MUL", 14, _(task).peek());

    task->code[pc++] = GP_OPCODE(GP_BINARY_OPERATION, GP_DIV);
    _(task).push(3);
    _(vm).pump();
    assert("DIV", 4, _(task).peek());

    task->code[pc++] = GP_OPCODE(GP_BINARY_OPERATION, GP_MOD);
    _(task).push(3);
    _(vm).pump();
    assert("MOD", 1, _(task).peek());

    task->code[pc++] = GP_STOP;
    _(vm).pump();
    _(vm).pump();
    _(vm).pump();
    return 0;
}