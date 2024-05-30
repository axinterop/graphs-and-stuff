#include "Stack.h"

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

void Stack::push(int data) {
    Node *newNode = new Node(data);
    newNode->next = top;
    top = newNode;
}

int Stack::peek() {
    if (!isEmpty())
        return top->data;
    else
        throw std::invalid_argument(".peek() on empty stack");
}

void Stack::pop() {
    Node *tmp = nullptr;
    if (top == nullptr) {
        std::cout << ".pop() on empty stack";
    } else {
        tmp = top;
        top = top->next;
    }
    delete tmp;
}

bool Stack::isEmpty() {
    return top == nullptr;
}

