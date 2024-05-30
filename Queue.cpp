#include "Queue.h"

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::enqueue(int data) {
    Node *newNode = new Node(data);
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void Queue::dequeue() {
    if (isEmpty()) {
        throw std::invalid_argument(".dequeue() on empty queue");
    } else {
        Node *tmp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete tmp;
    }
}

int Queue::peek() {
    if (!isEmpty())
        return front->data;
    else {
        throw std::invalid_argument(".peek() on empty queue");
    }
}

bool Queue::isEmpty() {
    return front == nullptr;
}

