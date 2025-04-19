#ifndef DECK_H
#define DECK_H

#include "dlist.h"

typedef enum typeDeckError {
    deckOk,
    deckEmpty,
    deckNotMem,
    deckEnd,
    deckStart,
} TypeDeckError;
TypeDeckError deckError = deckOk;

typedef Dlist Deck;


unsigned short IsEmptyDeck(Deck *D) {
    return Count(D) == 0;
}


void InitDeck(Deck *D) {
    InitDlist(D);
    BeginPtr(D);
    deckError = dlistError;
}


void PutDeckL(Deck *D, baseType E) {
    BeginPtr(D);
    PutDlistR(D, E);
    deckError = dlistError;
}


void PutDeckR(Deck *D, baseType E) {
    BeginPtr(D);
    PutDlistL(D, E);
    deckError = dlistError;
}


void ReadDeckL(Deck *D, baseType *E) {
    BeginPtr(D);
    ReadDlistR(D, E);
    deckError = dlistError;
}


void ReadDeckR(Deck *D, baseType *E) {
    BeginPtr(D);
    ReadDlistL(D, E);
    deckError = dlistError;
}


void GetDeckL(Deck *D, baseType *E) {
    BeginPtr(D);
    GetDlistR(D, E);
    deckError = dlistError;
}


void GetDeckR(Deck *D, baseType *E) {
    BeginPtr(D);
    GetDlistL(D, E);
    deckError = dlistError;
}


void CopyDeck(Deck *D1, Deck *D2) {
    CopyDlist(D1, D2);
    deckError = dlistError;
}


void DoneDeck(Deck *D) {
    DoneDlist(D);
    deckError = dlistError;
}


#endif //DECK_H