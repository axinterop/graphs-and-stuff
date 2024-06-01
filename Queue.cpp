#include "Queue.h"

Queue::Queue(int cap) {
    arr = new int[cap];
    capacity = cap;
    front = 0;
    rear = -1;
    size = 0;
}

Queue::~Queue() {
    if (arr != nullptr) {
        delete[] arr;
    }
}

void Queue::enqueue(int data) {
    if (isFull()) {
        throw std::overflow_error("Queue is full");
    } else {
        rear = (rear + 1) % capacity;
        arr[rear] = data;
        size++;
    }
}

void Queue::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    } else {
        front = (front + 1) % capacity;
        size--;
    }
}

int Queue::peek() {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");
    } else {
        return arr[front];
    }
}

bool Queue::isEmpty() {
    return size == 0;
}

bool Queue::isFull() {
    return size == capacity;
}
