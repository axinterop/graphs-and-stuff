#ifndef PROJECT3_QUEUE_H
#define PROJECT3_QUEUE_H

#include <stdexcept>

class Queue {
private:
    int *arr;
    int front;
    int rear;
    int capacity;
    int size;

public:
    explicit Queue(int cap);
    ~Queue();
    void enqueue(int data);
    void dequeue();
    int peek();
    bool isEmpty();
    bool isFull();
};

#endif //PROJECT3_QUEUE_H
