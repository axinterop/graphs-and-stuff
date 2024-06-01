#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H

#include <iostream>
#include <stdexcept>

using namespace std;

#include "Vertex.h"
#include "Stack.h"
#include "Queue.h"
#include "Vector.h"
#include "Vector.cpp"

class Graph {
private:
    Vector<Vertex*> vertices;
    int verticesNum;
    int size = 0;
    Vector<int> componentVertices;
public:
    Graph(): verticesNum(0) {}
    explicit Graph(int v): verticesNum(v), vertices(v, nullptr) {};
    ~Graph();

    Vertex& operator[](int index);

    void addVertex(int n, int incNum);
    void addIncident(int v, int inc);

    void print();
    void solve();

    void degreeSequence();
    void numberOfComponents();
    void isBipartite();
    void eccentricity();
    void isPlanar();
    void colorGreedy();
    void colorLF();
    void colorSLF();
    void numberOfC4();
    void numberOfComplementEdges();

};

#endif //PROJECT3_GRAPH_H
