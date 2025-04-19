#include <stdio.h>
#include <assert.h>

#include "stack.h"

void stackTest() {
    Stack s;
    InitStack(&s);
    int data = 12;
    baseType data_ = &data;
    GetStack(&s, &data_);
    assert(stackError == StackUnder);
    PutStack(&s, &data);
    assert(stackError == StackOk);
    ReadStack(&s, &data_);
    assert(stackError == StackOk && *(int *) (data_) == 12);
    data = 3;
    GetStack(&s, &data_);
    assert(stackError == StackOk && *(int *) (data_) == 3);
}

void test() {
    stackTest();
}

int main() {
    test();

    return 0;
}