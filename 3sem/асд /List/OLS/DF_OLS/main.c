#include "list.h"
#include <assert.h>


extern TypeListError listError;


void test1() {
    List L;

    int nums[] = {1, 2, 3, 4};

    InitList(&L);
    assert(listError == listOk && Count(&L) == 0);

    baseType data ;
    PutList(&L, &nums[0]);
    ReadList(&L, &data);
    assert(data == &nums[0] && listError == listOk);
    MovePtr(&L);
    PutList(&L, &nums[1]);
    MovePtr(&L);
    PutList(&L, &nums[2]);
    BeginPtr(&L);
    PutList(&L, &nums[3]);
    assert(listError == listOk && Count(&L) == 4);
    GetList(&L, &data);
    assert(data == &nums[3] && listError == listOk);
    GetList(&L, &data);
    assert(data == &nums[0] && listError == listOk);
    GetList(&L, &data);
    assert(data == &nums[1] && listError == listOk);
    GetList(&L, &data);
    assert(data == &nums[2] && listError == listOk);
    GetList(&L, &data);
    assert(listError == listEnd);

    DoneList(&L);
    assert(listError == listOk);
}


void test2() {
    List L1, L2;

    int nums1[] = {1, 2, 3, 4};

    int nums2[] = {5, 6};

    /*
    L1: ******
    L2: ***
    */

    InitList(&L1);
    InitList(&L2);

    for (int i = 0; i < 4; ++i) {
        PutList(&L1, &nums1[i]);
    }
    assert(listError == listOk);

    for (int i = 0; i < 2; ++i) {
        PutList(&L2, &nums2[i]);
    }
    assert(listError == listOk);

    CopyList(&L1, &L2);
    assert(Count(&L1) == Count(&L2));
    BeginPtr(&L1);
    BeginPtr(&L2);
    for (int i = 0; i < 4; ++i) {
        baseType data1, data2;
        ReadList(&L1, &data1);
        ReadList(&L2, &data2);
        assert(data1 == data2 && listError == listOk);
        MovePtr(&L1);
        MovePtr(&L2);
    }

    DoneList(&L1);
    assert(listError == listOk);
    DoneList(&L2);
    assert(listError == listOk);

    /*
    L1: ******
    L2: ***********
    */

    InitList(&L1);
    InitList(&L2);

    for (int i = 0; i < 4; ++i) {
        PutList(&L1, &nums2[i]);
    }
    assert(listError == listOk);

    for (int i = 0; i < 2; ++i) {
        PutList(&L2, &nums1[i]);
    }
    assert(listError == listOk);

    CopyList(&L1, &L2);
    assert(Count(&L1) == Count(&L2));
    BeginPtr(&L1);
    BeginPtr(&L2);
    for (int i = 0; i < 4; ++i) {
        baseType data1, data2;
        ReadList(&L1, &data1);
        ReadList(&L2, &data2);
        assert(data1 == data2 && listError == listOk);
        MovePtr(&L1);
        MovePtr(&L2);
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
