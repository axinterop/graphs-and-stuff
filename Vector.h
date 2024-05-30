#ifndef PROJECT3_VECTOR_H
#define PROJECT3_VECTOR_H

#include <cstddef>


template <typename T>
class Vector {
private:
    T* arr;
    size_t capacity;
    size_t size;

public:
    Vector() : capacity(1), size(0), arr(new T[1]) {}
    explicit Vector(size_t cap) : capacity(cap), size(0), arr(new T[cap]) {}
    Vector(size_t cap, const T& val) : capacity(cap), size(cap), arr(new T[cap]) {
        for (size_t i = 0; i < size; ++i) {
            arr[i] = val;
        }
    }
    ~Vector() { delete[] arr; }

    void push_back(const T& val);
    void pop_back();

    size_t get_size() const { return size; }
    size_t get_capacity() const { return capacity; }

    T& operator[](size_t index) { return arr[index]; }
    const T& operator[](size_t index) const { return arr[index]; }

    T* begin() { return arr; }
    const T* begin() const { return arr; }
    T* end() { return arr + size; }
    const T* end() const { return arr + size; }
};



#endif //PROJECT3_VECTOR_H
