#include "Graph.h"

bool descending(int a, int b) {
    return a > b;
}

Graph::~Graph() {
    for (int v = 0; v < verticesNum; v++) {
        delete vertices[v];
    }
    delete[] vertices;
}

Vertex &Graph::operator[](int index) {
    if (index < 0 || index >= verticesNum) {
        cout << "Index out of bounds" << endl;
        exit(1);
    }
    return *vertices[index];
}

void Graph::addVertex(int incNum) {
    if (free_v_id >= verticesNum) {
        throw std::invalid_argument("free_v_id exceeded verticesNum");
    }
    vertices[free_v_id++] = new Vertex(incNum);
}

void Graph::addIncident(int v, int inc) {
    vertices[v]->addIncident(inc);
}

void Graph::print() {
    for (int v = 0; v < verticesNum; v++) {
        cout << v << ": ";
        vertices[v]->print();
        cout << "\n";
    }
}

void Graph::solve() {
    degreeSequence();
    numberOfComponents();
    isBipartite();
    eccentricity();
    isPlanar();
    colorGreedy();
    colorLF();
    colorSLF();
    numberOfC4();
    numberOfComplementEdges();
}

void Graph::degreeSequence() {
    int degrees[verticesNum];
    for (int v = 0; v < verticesNum; v++)
        degrees[v] = vertices[v]->getDegree();
    // TODO: Implement sort algorithm
    std::sort(degrees, degrees + verticesNum, descending);
    for (int v = 0; v < verticesNum; v++)
        cout << degrees[v] << " ";
    cout << endl;
}

void Graph::numberOfComponents() {
    // TODO: Implement
    cout << '?' << endl;
}

void Graph::isBipartite() {
    // TODO: Implement
    cout << '?' << endl;
}

void Graph::eccentricity() {

}

void Graph::isPlanar() {
    // TODO: Implement
    cout << '?' << endl;
}

void Graph::colorGreedy() {
    // TODO: Implement
    cout << '?' << endl;
}

void Graph::colorLF() {
    // TODO: Implement
    cout << '?' << endl;
}

void Graph::colorSLF() {
    // TODO: Implement
    cout << '?' << endl;
}

void Graph::numberOfC4() {
    // TODO: Implement
    cout << '?' << endl;
}

void Graph::numberOfComplementEdges() {
    // TODO: Change to long long int?
    int complementEdgeNum = verticesNum * (verticesNum - 1);
    for (int v = 0; v < verticesNum; v++)
        complementEdgeNum -= vertices[v]->getDegree();
    complementEdgeNum /= 2;
    cout << complementEdgeNum << endl;
}
