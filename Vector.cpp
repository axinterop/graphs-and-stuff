#include "Vector.h"

template <typename T>
void Vector<T>::copy(const Vector& other) {
    arr = new T[other.capacity];
    capacity = other.capacity;
    size = other.size;
    for (size_t i = 0; i < size; ++i) {
        arr[i] = other.arr[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] arr;
        copy(other);
    }
    return *this;
}

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
