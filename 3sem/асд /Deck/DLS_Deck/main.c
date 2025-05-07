#include "deck.h"
#include <assert.h>


extern TypeDeckError deckError;


void test1() {
    Deck DL;

    int nums[] = {1, 2, 3, 4};

    InitDeck(&DL);
    assert(deckError == deckOk && Count(&DL) == 0);
    baseType data;
    PutDeckR(&DL, &nums[1]);
    assert(deckError == deckOk);
    ReadDeckL(&DL, &data);
    assert(data == &nums[1] && deckError == deckOk);
    GetDeckL(&DL, &data);
    assert(data == &nums[1] && deckError == deckOk);

    PutDeckL(&DL, &nums[1]);
    assert(deckError == deckOk);
    PutDeckL(&DL, &nums[0]);
    assert(deckError == deckOk);
    PutDeckR(&DL, &nums[2]);
    assert(deckError == deckOk);
    PutDeckR(&DL, &nums[3]);
    assert(deckError == deckOk);

    GetDeckR(&DL, &data);
    assert(data == &nums[3] && deckError == deckOk);
    GetDeckL(&DL, &data);
    assert(data == &nums[0] && deckError == deckOk);
    GetDeckR(&DL, &data);
    assert(data == &nums[2] && deckError == deckOk);
    GetDeckL(&DL, &data);
    assert(data == &nums[1] && deckError == deckOk);
    GetDeckR(&DL, &data);
    assert(deckError == deckStart);
    GetDeckL(&DL, &data);
    assert(deckError == deckEnd);

    DoneDeck(&DL);
    assert(deckError == deckOk);
}


void test2() {
    Deck L1, L2;

    int nums1[] = {1, 2, 3, 4};

    int nums2[] = {5, 6};

    /*
    L1: ******
    L2: ***
    */

    InitDeck(&L1);
    InitDeck(&L2);

    for (int i = 0; i < 4; ++i) {
        PutDeckR(&L1, &nums1[i]);
    }
    assert(deckError == deckOk);

    for (int i = 0; i < 2; ++i) {
        PutDeckL(&L2, &nums2[i]);
    }
    assert(deckError == deckOk);

    CopyDeck(&L1, &L2);
    assert(Count(&L1) == Count(&L2));
    for (int i = 0; i < 4; ++i) {
        baseType data1, data2;
        GetDeckR(&L1, &data1);
        GetDeckR(&L2, &data2);
        assert(data1 == data2 && deckError == deckOk);
    }

    DoneDeck(&L1);
    assert(deckError == deckOk);
    DoneDeck(&L2);
    assert(deckError == deckOk);

    /*
    L1: ******
    L2: ***********
    */

    InitDeck(&L1);
    InitDeck(&L2);

    for (int i = 0; i < 4; ++i) {
        PutDeckL(&L1, &nums2[i]);
    }
    assert(deckError == deckOk);

    for (int i = 0; i < 2; ++i) {
        PutDeckR(&L1, &nums2[i]);
    }
    assert(deckError == deckOk);

    CopyDeck(&L1, &L2);
    assert(Count(&L1) == Count(&L2));
    for (int i = 0; i < 4; ++i) {
        baseType data1, data2;
        GetDeckL(&L1, &data1);
        GetDeckL(&L2, &data2);
        assert(data1 == data2 && deckError == deckOk);
    }
}


void test() {
    test1();
    test2();
}


int main() {
    test();

    return 0;
}
