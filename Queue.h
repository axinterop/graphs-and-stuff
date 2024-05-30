#ifndef PROJECT3_QUEUE_H
#define PROJECT3_QUEUE_H

#include <stdexcept>

#include "Node.h"

class Queue {
private:
    Node *front;
    Node *rear;
public:
    Queue() { front = rear = nullptr; };
    ~Queue();
    void enqueue(int data);
    void dequeue();
    int peek();
    bool isEmpty();
};



#endif //PROJECT3_QUEUE_H
