#ifndef STACK_H
#define STACK_H

#define SIZE_STACK 1000

typedef enum typeStackError {
    StackOk,
    StackOver,
    StackUnder,
} TypeStackError;
TypeStackError stackError = StackOk; // Переменная ошибок

typedef void *baseType; // Определить тип элемента стека

typedef struct stack {
    baseType array[SIZE_STACK];
    unsigned int ptr; /* Указывает на элемент, являющийся вершиной стека */
} Stack;


void InitStack(Stack *s) { // Инициализация стека
    s->ptr = 0;
    stackError = StackOk;
}


unsigned short IsEmptyStack(Stack *s) { // Проверка: стек пуст?
    return s->ptr == 0;
}


void PutStack(Stack *s, baseType E) { /* Поместить элемент в стек */
    if (SIZE_STACK - 1 == s->ptr) {
        stackError = StackOver;
        return;
    } else {
        s->array[++s->ptr] = E;
    }
    stackError = StackOk;
}


void ReadStack(Stack *s, baseType *E) { /* Прочитать элемент из вершины стека */
    if (IsEmptyStack(s)) {
        stackError = StackUnder;
        return;
    } else {
        *E = s->array[s->ptr];
    }
    stackError = StackOk;
}


void GetStack(Stack *s, baseType *E) { /* Извлечь элемент из стека */
    if (IsEmptyStack(s)) {
        stackError = StackUnder;
        return;
    } else {
        ReadStack(s, E);
        s->ptr--;
    }
    stackError = StackOk;
}


#endif //STACK_H
