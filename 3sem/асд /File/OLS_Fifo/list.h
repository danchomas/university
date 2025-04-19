#ifndef LIST_H
#define LIST_H

#include <malloc.h>

typedef enum typeListError {
    listOk,
    listNotMem,
    listEnd,
} TypeListError;
TypeListError listError = listOk;

typedef void *baseType;
typedef void *ptrToElement;

typedef struct element {
    baseType el;
    ptrToElement ptrNextEl;
} Element;

typedef struct list {
    ptrToElement PMemList;
    ptrToElement ptr;
    unsigned int sizeList; // длина списка
} List;


void InitList(List *L) {
    L->PMemList = (ptrToElement) malloc((sizeof(Element)));
    if (L->PMemList == NULL) {
        listError = listNotMem;
        return;
    } else {
        *((Element *) L->PMemList) = (Element) {NULL, NULL};
        L->ptr = L->PMemList;
        L->sizeList = 1;
    }
    listError = listOk;
}


int Count(List *L) {
    return L->sizeList - 1;
}


int IsEndList(List *L) {
    return ((Element *) L->ptr)->ptrNextEl == NULL;
}


int IsEmptyList(List *L) {
    return Count(L) == 0;
}


void BeginPtr(List *L) {
    L->ptr = L->PMemList;
}


void MovePtr(List *L) {
    if (((Element *) L->ptr)->ptrNextEl == NULL) {
        listError = listEnd;
    } else {
        L->ptr = ((Element *) L->ptr)->ptrNextEl;
    }
    listError = listOk;
}


void EndPtr(List *L) {
    listError = listOk;
    while (!IsEndList(L) && listError == listOk) {
        MovePtr(L);
    }
}


void MoveTo(List *L, unsigned int n) {
    BeginPtr(L);
    listError = listOk;
    while (n-- && listError == listOk) {
        MovePtr(L);
    }
}


void PutList(List *L, baseType E) {
    ptrToElement newElement = (ptrToElement) malloc((sizeof(Element)));
    if (newElement == NULL) {
        listError = listNotMem;
        return;
    } else {
        ((Element *) newElement)->el = E;
        if (IsEndList(L)) {
            ((Element *) newElement)->ptrNextEl = NULL;
            ((Element *) L->ptr)->ptrNextEl = newElement;
        } else {
            ((Element *) newElement)->ptrNextEl = ((Element *) L->ptr)->ptrNextEl;
            ((Element *) L->ptr)->ptrNextEl = newElement;
        }
        L->sizeList++;
    }
    listError = listOk;
}


void ReadList(List *L, baseType *E) {
    if (IsEndList(L)) {
        listError = listEnd;
        return;
    } else {
        ptrToElement nextElPtr = ((Element *) L->ptr)->ptrNextEl;
        *E = ((Element *) nextElPtr)->el;
    }
    listError = listOk;
}


void GetList(List *L, baseType *E) {
    if (IsEndList(L)) {
        listError = listEnd;
        return;
    } else {
        ReadList(L, E);
        Element *NeedToDel = ((Element *) L->ptr)->ptrNextEl;
        ((Element *) L->ptr)->ptrNextEl = NeedToDel->ptrNextEl;
        free(NeedToDel);
        L->sizeList--;
    }
    listError = listOk;
}


void DoneList(List *L) {
    BeginPtr(L);
    while (Count(L) != 0) {
        baseType buf;
        GetList(L, &buf);
    }
    free(L->PMemList);

    listError = listOk;
}


void CopyList(List *L1, List *L2) {
    BeginPtr(L1);
    BeginPtr(L2);
    unsigned changed = 0;
    listError = listOk;

    while (IsEndList(L2) &&
           changed < Count(L1) &&
           changed < Count(L2) &&
           listError == listOk) {
        ((Element *) L2->ptr)->el = ((Element *) L1->ptr)->el;
        MovePtr(L2);
        MovePtr(L1);
        changed++;
    }

    while (changed < Count(L1) &&
           listError == listOk) {
        baseType data;
        ReadList(L1, &data);
        PutList(L2, data);
        MovePtr(L2);
        MovePtr(L1);
        changed++;
    }

    while (Count(L2) > Count(L1) &&
           listError == listOk) {
        baseType buf;
        GetList(L2, &buf);
    }

}


#endif //LIST_H
