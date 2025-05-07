#ifndef DLIST_H
#define DLIST_H

#include <malloc.h>

typedef enum typeDlistError {
    dlistOk,
    dlistEmpty,
    dlistNotMem,
    dlistEnd,
    dlistStart,
} TypeDlistError;
TypeDlistError dlistError = dlistOk;

typedef void *baseType;
typedef void *ptrToElement;

typedef struct element {
    baseType data;
    ptrToElement lLink;
    ptrToElement rLink;
} Element;

typedef struct dlist {
    ptrToElement PMemList;
    ptrToElement ptr;
    int sizeList; // длина списка
} Dlist;


void InitDlist(Dlist *DL) {
    DL->PMemList = (ptrToElement) malloc((sizeof(Element)));
    if (DL->PMemList == NULL) {
        dlistError = dlistNotMem;
        return;
    } else {
        *((Element *) DL->PMemList) = (Element) {NULL, NULL, NULL};
        DL->ptr = DL->PMemList;
        DL->sizeList = 1;
    }
    dlistError = dlistOk;
}


int Count(Dlist *DL) {
    return DL->sizeList - 1;
}


int IsEndDlist(Dlist *DL) {
    return ((Element *) DL->ptr)->rLink == NULL;
}

int IsStartDlist(Dlist *DL) {
    return ((Element *) DL->ptr)->lLink == NULL;
}


void BeginPtr(Dlist *DL) {
    DL->ptr = DL->PMemList;
}


void EndPtr(Dlist *DL) {
    DL->ptr = ((Element *) DL->PMemList)->lLink;
}


void MovePtrL(Dlist *DL) {
    if (DL->ptr == DL->PMemList &&
        ((Element *) DL->ptr)->lLink == NULL &&
        ((Element *) DL->ptr)->rLink == NULL) {
        dlistError = dlistEmpty;
    } else if (((Element *) DL->ptr)->lLink == NULL) {
        dlistError = dlistStart;
    }
    DL->ptr = ((Element *) DL->ptr)->lLink;
    dlistError = dlistOk;
}


void MovePtrR(Dlist *DL) {
    if (DL->ptr == DL->PMemList &&
        ((Element *) DL->ptr)->lLink == NULL &&
        ((Element *) DL->ptr)->rLink == NULL) {
        dlistError = dlistEmpty;
    } else if (((Element *) DL->ptr)->rLink == NULL) {
        dlistError = dlistEnd;
    }
    DL->ptr = ((Element *) DL->ptr)->rLink;
    dlistError = dlistOk;
}


void PutDlistR(Dlist *DL, baseType E) {
    ptrToElement newElement = (ptrToElement) malloc((sizeof(Element)));
    if (newElement == NULL) {
        dlistError = dlistNotMem;
        return;
    } else {
        if (DL->PMemList == DL->ptr) {
            ptrToElement startElement = ((Element *) DL->ptr)->rLink;
            *((Element *) newElement) = (Element) {E, NULL, startElement};
            ((Element *) DL->ptr)->rLink = newElement;

            if (startElement != NULL) {
                ((Element *) startElement)->lLink = newElement;
            } else {
                ((Element *) DL->ptr)->lLink = newElement;
            }

        } else if (((Element *) DL->PMemList)->lLink == DL->ptr) {
            *((Element *) newElement) = (Element) {E, DL->ptr, NULL};
            ((Element *) DL->ptr)->rLink = newElement;
            ((Element *) DL->PMemList)->lLink = newElement;
        } else {
            ptrToElement nextElement = ((Element *) DL->ptr)->rLink;
            *((Element *) newElement) = (Element) {E, DL->ptr, nextElement};
            ((Element *) DL->ptr)->rLink = newElement;
            ((Element *) nextElement)->lLink = newElement;
        }
        DL->sizeList++;
    }
    dlistError = dlistOk;
}


void PutDlistL(Dlist *DL, baseType E) {
    ptrToElement newElement = (ptrToElement) malloc((sizeof(Element)));
    if (newElement == NULL) {
        dlistError = dlistNotMem;
        return;
    } else {
        if (DL->PMemList == DL->ptr) {
            ptrToElement lastElement = ((Element *) DL->ptr)->lLink;
            *((Element *) newElement) = (Element) {E, lastElement, NULL};
            ((Element *) DL->ptr)->lLink = newElement;

            if (lastElement != NULL) {
                ((Element *) lastElement)->rLink = newElement;
            }  else {
                ((Element *) DL->ptr)->rLink = newElement;
            }
        } else if (((Element *) DL->PMemList)->rLink == DL->ptr) {
            *((Element *) newElement) = (Element) {E, NULL, DL->ptr};
            ((Element *) DL->PMemList)->rLink = newElement;
            ((Element *) DL->ptr)->lLink = newElement;
        } else {
            ptrToElement previousElement = ((Element *) DL->ptr)->lLink;
            *((Element *) newElement) = (Element) {E, previousElement, DL->ptr};
            ((Element *) previousElement)->rLink = newElement;
            ((Element *) DL->ptr)->lLink = newElement;
        }
        DL->sizeList++;
    }
    dlistError = dlistOk;
}


void ReadDlistR(Dlist *DL, baseType *E) {
    if (((Element *) DL->ptr)->rLink == NULL) {
        dlistError = dlistEnd;
        return;
    } else {
        ptrToElement nextElement = ((Element *) DL->ptr)->rLink;
        *E = ((Element *) nextElement)->data;
    }
    dlistError = dlistOk;
}


void ReadDlistL(Dlist *DL, baseType *E) {
    if (((Element *) DL->ptr)->lLink == NULL) {
        dlistError = dlistStart;
        return;
    } else {
        ptrToElement previousElement = ((Element *) DL->ptr)->lLink;
        *E = ((Element *) previousElement)->data;
    }
    dlistError = dlistOk;
}


void GetDlistR(Dlist *DL, baseType *E) {
    if (IsEndDlist(DL)) {
        dlistError = dlistEnd;
        return;
    } else {
        ptrToElement delElement = ((Element *) DL->ptr)->rLink;
        ReadDlistR(DL, E);

        if (((Element *) delElement)->rLink == NULL) {
            ((Element *) DL->ptr)->rLink = NULL;
            if (DL->PMemList == DL->ptr) {
                ((Element *) DL->PMemList)->rLink = NULL;
                ((Element *) DL->PMemList)->lLink = NULL;
            } else {
                ((Element *) DL->PMemList)->lLink = DL->ptr;
            }
        } else {
            ptrToElement nextElement = ((Element *) delElement)->rLink;
            ((Element *) DL->ptr)->rLink = nextElement;
            if (DL->ptr == DL->PMemList) {
                ((Element *) nextElement)->lLink = NULL;
            } else {
                ((Element *) nextElement)->lLink = DL->ptr;
            }
        }
        free(delElement);
        DL->sizeList--;
    }
    dlistError = dlistOk;
}


void GetDlistL(Dlist *DL, baseType *E) {
    if (IsStartDlist(DL)) {
        dlistError = dlistStart;
        return;
    } else {
        ptrToElement delElement = ((Element *) DL->ptr)->lLink;
        ReadDlistL(DL, E);

        if (((Element *) delElement)->lLink == NULL) {
            ((Element *) DL->ptr)->lLink = NULL;
            if (DL->PMemList == DL->ptr) {
                ((Element *) DL->PMemList)->rLink = NULL;
                ((Element *) DL->PMemList)->lLink = NULL;
            } else {
                ((Element *) DL->PMemList)->rLink = DL->ptr;
            }
        } else {
            ptrToElement previousElement = ((Element *) delElement)->lLink;
            ((Element *) DL->ptr)->lLink = previousElement;
            if (DL->ptr == DL->PMemList) {
                ((Element *) previousElement)->rLink = NULL;
            } else {
                ((Element *) previousElement)->rLink = DL->ptr;
            }

        }
        free(delElement);
        DL->sizeList--;
    }
    dlistError = dlistOk;
}


void DoneDlist(Dlist *DL) {
    BeginPtr(DL);
    while (Count(DL) != 0) {
        baseType buf;
        GetDlistR(DL, &buf);
    }
    free(DL->PMemList);

    dlistError = dlistOk;
}


void CopyDlist(Dlist *DL1, Dlist *DL2) {
    BeginPtr(DL1);
    BeginPtr(DL2);
    unsigned changed = 0;
    dlistError = dlistOk;

    while (IsEndDlist(DL2) &&
           changed < Count(DL1) &&
           changed < Count(DL2) &&
           dlistError == dlistOk) {
        baseType data;
        ReadDlistR(DL1, &data);

        PutDlistR(DL2, data);

        MovePtrR(DL2);
        MovePtrR(DL1);
        changed++;
    }

    while (changed < Count(DL1) &&
           dlistError == dlistOk) {
        baseType data;
        ReadDlistR(DL1, &data);

        PutDlistR(DL2, data);

        MovePtrR(DL2);
        MovePtrR(DL1);
        changed++;
    }

    while (Count(DL2) > Count(DL1) &&
           dlistError == dlistOk) {
        baseType buf;
        GetDlistR(DL2, &buf);
    }
}


#endif //DLIST_H
