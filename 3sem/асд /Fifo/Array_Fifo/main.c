#include "fifo.h"
#include <assert.h>


extern TypeFifoError fifoError;


void test1() {
    Fifo F;

    int nums[] = {1, 2, 3, 4};

    InitFifo(&F);
    assert(fifoError == fifoOk && Count(&F) == 0);
    baseType data;
    GetFifo(&F, &data);
    assert(fifoError == fifoEmpty);
    PutFifo(&F, &nums[0]);
    assert(fifoError == fifoOk);
    PutFifo(&F, &nums[1]);
    assert(fifoError == fifoOk);
    PutFifo(&F, &nums[2]);
    assert(fifoError == fifoOk);
    PutFifo(&F, &nums[3]);
    assert(fifoError == fifoOk);

    GetFifo(&F, &data);
    assert(data == &nums[0] && fifoError == fifoOk);
    GetFifo(&F, &data);
    assert(data == &nums[1] && fifoError == fifoOk);
    GetFifo(&F, &data);
    assert(data == &nums[2] && fifoError == fifoOk);
    GetFifo(&F, &data);
    assert(data == &nums[3] && fifoError == fifoOk);

    GetFifo(&F, &data);
    assert(fifoError == fifoEmpty);

    DoneFifo(&F);
    assert(fifoError == fifoOk);
}


void test2() {
    Fifo F1, F2;

    int nums1[] = {1, 2, 3, 4};

    int nums2[] = {5, 6};

    /*
    F1: ******
    F2: ***
    */

    InitFifo(&F1);
    InitFifo(&F2);

    for (int i = 0; i < 4; ++i) {
        PutFifo(&F1, &nums1[i]);
    }
    assert(fifoError == fifoOk);

    for (int i = 0; i < 2; ++i) {
        PutFifo(&F2, &nums2[i]);
    }
    assert(fifoError == fifoOk);

    CopyFifo(&F1, &F2);
    assert(Count(&F1) == Count(&F2));
    for (int i = 0; i < 4; ++i) {
        baseType data1, data2;
        GetFifo(&F1, &data1);
        GetFifo(&F2, &data2);
        assert(data1 == data2 && fifoError == fifoOk);
    }

    DoneFifo(&F1);
    assert(fifoError == fifoOk);
    DoneFifo(&F2);
    assert(fifoError == fifoOk);

    /*
    F1: ******
    F2: ***********
    */

    InitFifo(&F1);
    InitFifo(&F2);

    for (int i = 0; i < 4; ++i) {
        PutFifo(&F1, &nums2[i]);
    }
    assert(fifoError == fifoOk);

    for (int i = 0; i < 2; ++i) {
        PutFifo(&F2, &nums1[i]);
    }
    assert(fifoError == fifoOk);

    CopyFifo(&F1, &F2);
    assert(Count(&F1) == Count(&F2));
    for (int i = 0; i < 4; ++i) {
        baseType data1, data2;
        GetFifo(&F1, &data1);
        GetFifo(&F2, &data2);
        assert(data1 == data2 && fifoError == fifoOk);
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
