#ifndef PROJECT3_NODE_H
#define PROJECT3_NODE_H

class Node {
public:
    int data;
    Node *next;
    explicit Node (int d): data(d), next(nullptr) {};
};

#endif //PROJECT3_NODE_H
