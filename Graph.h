#ifndef PROJECT3_GRAPH_H
#define PROJECT3_GRAPH_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

#include "Vertex.h"

class Graph {
private:
    Vertex **vertices;
    int verticesNum;
    int free_v_id = 0;
public:
    Graph(): vertices(nullptr), verticesNum(0) {}
    explicit Graph(int v): verticesNum(v), vertices(new Vertex*[v]) {};
    ~Graph();

    Vertex& operator[](int index);

    void addVertex(int incNum);
    void addIncident(int v, int inc);

    void DFS();

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
