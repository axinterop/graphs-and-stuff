#include "Vector.h"

template <typename T>
void Vector<T>::push_back(const T& val) {
        if (size == capacity) {
            capacity *= 2;
            T* new_arr = new T[capacity];
            for (size_t i = 0; i < size; i++) {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }
        arr[size++] = val;
    }

template <typename T>
void Vector<T>::pop_back() {
    if (size > 0) size--;
}
