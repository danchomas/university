#ifndef FIFO_H
#define FIFO_H

#define FIFO_SIZE 1000

typedef enum typeFifoError {
    fifoOk,
    fifoEmpty,
    fifoFull,
} TypeFifoError;
TypeFifoError fifoError = fifoOk;

typedef void *baseType;

typedef struct fifo{
    baseType array[FIFO_SIZE];
    unsigned int size;
} Fifo;


unsigned int Count(Fifo *F) {
    return F->size;
}


unsigned int IsFifoFull(Fifo *F) {
    return Count(F) == FIFO_SIZE;
}


unsigned int IsFifoEmpty(Fifo *F) {
    return Count(F) == 0;
}


void InitFifo(Fifo *F) {
    F->size = 0;
    fifoError = fifoOk;
}


void PutFifo(Fifo *F, baseType E) {
    if (IsFifoFull(F)) {
        fifoError = fifoFull;
        return;
    } else {
        F->array[F->size++] = E;
    }
    fifoError = fifoOk;
}


void GetFifo(Fifo *F, baseType *E) {
    if (IsFifoEmpty(F)) {
        fifoError = fifoEmpty;
        return;
    } else {
        *E = F->array[0];
        for (int i = 1; i < F->size; i++) {
            F->array[i - 1] = F->array[i];
        }
        F->size--;
    }
    fifoError = fifoOk;
}


void DoneFifo(Fifo *F) {
    while (Count(F)) {
        baseType buf;
        GetFifo(F, &buf);
    }
    fifoError = fifoOk;
}


void CopyFifo(Fifo *F1, Fifo *F2) {
    for (int i = 0; i < Count(F1); i++) {
        F2->array[i] = F1->array[i];
    }
    F2->size = F1->size;

    fifoError = fifoOk;
}


#endif //FIFO_H
