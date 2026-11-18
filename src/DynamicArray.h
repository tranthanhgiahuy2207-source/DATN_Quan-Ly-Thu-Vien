#include "DynamicArray.h"

void DynamicArray::pushBack(const GiaoDich& gd) {
    if (n >= cap) {
        cap *= 2;
        GiaoDich* tmp = new GiaoDich[cap];
        for (int i = 0; i < n; ++i) tmp[i] = arr[i];
        delete[] arr;
        arr = tmp;
    }
    arr[n++] = gd;
}
