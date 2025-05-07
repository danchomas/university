#ifndef FILE_H
#define FILE_H

#include "fifo.h"

typedef enum typeFileError {
    fileOk,
    fileNotMem,
    fileEmpty,
} TypeFileError;

typedef struct file {
    Fifo input;
    Fifo output;
} File;

TypeFileError fileError = fileOk;

int IsEmptyFile(File *F) {
    return IsEmptyFifo(&F->output);
}

void InitFile(File *F) {
    InitFifo(&F->input);
    InitFifo(&F->output);
    fileError = fifoError;
}

void ReadFile(File *F, baseType *E) {
    if (IsEmptyFile(F)) {
        return;
    } else {
        GetFifo(&F->output, E);
        PutFifo(&F->input, *E);
    }
    fileError = fifoError;
}


void PutFile(File *F, baseType E) {
    PutFifo(&F->output, E);
    fileError = fifoError;
}


void BeginPtrFile(File *F) {
    while (!IsEmptyFile(F) && fileError == fileOk) {
        baseType E;
        GetFifo(&F->input, &E);
        PutFifo(&F->output, E);
        fileError = fifoError;
    }
}

#endif //FILE_H
