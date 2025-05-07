#ifndef FIFO_H
#define FIFO_H

#include "list.h"

typedef enum typeFifoError {
    fifoOk,
    fifoNotMem,
    fifoEmpty,
} TypeFifoError;


TypeFifoError fifoError = fifoOk;

typedef List Fifo;


void InitFifo(Fifo *F) {
    InitList(F);
    fifoError = listError;
}


void PutFifo(Fifo *F, baseType E) {
    EndPtr(F);
    PutList(F, E);
    fifoError = listError;
}


void GetFifo(Fifo *F, baseType *E) {
    BeginPtr(F);
    GetList(F, E);
    fifoError = listError;
}


void DoneFifo(Fifo *F) {
    DoneList(F);
    fifoError = listError;
}


void CopyFifo(Fifo *F1, Fifo *F2) {
    CopyList(F1, F2);
    fifoError = listError;
}


int IsEmptyFifo(Fifo *F) {
    IsEmptyList(F);
}

#endif //FIFO_H
