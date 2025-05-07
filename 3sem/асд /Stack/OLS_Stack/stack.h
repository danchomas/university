#ifndef STACK_H
#define STACK_H

#include "list.h"

typedef enum typeStackError {
    stackOk,
    stackNotMem,
    stackOver,
} TypeStackError;
TypeStackError stackError = stackOk; // Переменная ошибок

typedef void *baseType; // Определить тип элемента стека

typedef List Stack;


void InitStack(Stack *s) { // Инициализация стека
    InitList(s);
    stackError = listError;
}


unsigned short IsEmptyStack(Stack *s) { // Проверка: стек пуст?
    return Count(s) == 0;
}


void PutStack(Stack *s, baseType E) { /* Поместить элемент в стек */
    PutList(s, E);
    stackError = listError;
}


void ReadStack(Stack *s, baseType *E) { /* Прочитать элемент из вершины стека */
    ReadList(s, E);
    stackError = listError;
}


void GetStack(Stack *s, baseType *E) { /* Извлечь элемент из стека */
    GetList(s, E);
    stackError = listError;
}


#endif //STACK_H
