#include "dlist.h"
#include <assert.h>


extern TypeDlistError ddlistError;


void test1() {
    Dlist DL;

    int nums[] = {1, 2, 3, 4};

    InitList(&DL);
    assert(dlistError == dlistOk && Count(&DL) == 0);
    BeginPtr(&DL);
    baseType data;
    PutDlistR(&DL, &nums[1]);
    assert(dlistError == dlistOk);
    MovePtrR(&DL);
    ReadDlistL(&DL, &data);
    assert(dlistError == dlistStart);
    PutDlistL(&DL, &nums[0]);
    PutDlistR(&DL, &nums[3]);
    PutDlistR(&DL, &nums[2]);

    BeginPtr(&DL);
    GetDlistR(&DL, &data);
    assert(data == &nums[0] && dlistError == dlistOk);
    GetDlistR(&DL, &data);
    assert(data == &nums[1] && dlistError == dlistOk);
    GetDlistR(&DL, &data);
    assert(data == &nums[2] && dlistError == dlistOk);
    GetDlistL(&DL, &data);
    assert(data == &nums[3] && dlistError == dlistOk);
    GetDlistR(&DL, &data);
    assert(dlistError == dlistEnd);
    GetDlistL(&DL, &data);
    assert(dlistError == dlistStart);

    DoneDlist(&DL);
    assert(dlistError == dlistOk);
}


void test2() {
    Dlist L1, L2;

    int nums1[] = {1, 2, 3, 4};

    int nums2[] = {5, 6};

    /*
    L1: ******
    L2: ***
    */

    InitList(&L1);
    InitList(&L2);

    for (int i = 0; i < 4; ++i) {
        PutDlistR(&L1, &nums1[i]);
        MovePtrR(&L1);
    }
    assert(dlistError == dlistOk);

    for (int i = 0; i < 2; ++i) {
        PutDlistL(&L2, &nums2[i]);
        MovePtrR(&L2);
    }
    assert(dlistError == dlistOk);

    CopyDlist(&L1, &L2);
    assert(Count(&L1) == Count(&L2));
    BeginPtr(&L1);
    BeginPtr(&L2);
    for (int i = 0; i < 4; ++i) {
        baseType data1, data2;
        ReadDlistR(&L1, &data1);
        ReadDlistR(&L2, &data2);
        assert(data1 == data2 && dlistError == dlistOk);
        MovePtrR(&L1);
        MovePtrR(&L2);
    }

    DoneDlist(&L1);
    assert(dlistError == dlistOk);
    DoneDlist(&L2);
    assert(dlistError == dlistOk);

    /*
    L1: ******
    L2: ***********
    */

    InitList(&L1);
    InitList(&L2);

    for (int i = 0; i < 4; ++i) {
        PutDlistR(&L1, &nums2[i]);
        MovePtrR(&L1);
    }
    assert(dlistError == dlistOk);

    for (int i = 0; i < 2; ++i) {
        PutDlistR(&L1, &nums2[i]);
        MovePtrR(&L1);
    }
    assert(dlistError == dlistOk);

    CopyDlist(&L1, &L2);
    assert(Count(&L1) == Count(&L2));
    BeginPtr(&L1);
    BeginPtr(&L2);
    for (int i = 0; i < 4; ++i) {
        baseType data1, data2;
        ReadDlistR(&L1, &data1);
        ReadDlistR(&L2, &data2);
        assert(data1 == data2 && dlistError == dlistOk);
        MovePtrR(&L1);
        MovePtrR(&L2);
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
