#ifndef PROJECT3_STACK_H
#define PROJECT3_STACK_H

#include <stdexcept>
#include <iostream>

#include "Node.h"

class Stack {
private:
    Node *top;
public:
    Stack(): top(nullptr) {};
    ~Stack();
    void push(int data);
    int peek();
    void pop();
    bool isEmpty();
};


#endif //PROJECT3_STACK_H
