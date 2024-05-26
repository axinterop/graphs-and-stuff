#include "Graph.h"

bool descending(int a, int b) { return a > b; }

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

void Graph::addIncident(int v, int inc) { vertices[v]->addIncident(inc); }

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
    bool candidateForComponent[verticesNum];
    for (int i = 0; i < verticesNum; i++)
        candidateForComponent[i] = true;

    int startVertex = 0;
    int componentsCount = 0;

    for (int c = 0; c < verticesNum; c++) {
        if (!candidateForComponent[c])
            continue;

        startVertex = c;

        bool visited[verticesNum] = {};
        // TODO: Implement custom stack
        stack<int> unvisited;
        unvisited.push(startVertex);

        while (!unvisited.empty()) {
            int currentV = unvisited.top();
            unvisited.pop();

            if (visited[currentV])
                continue;

            visited[currentV] = true;
            // currentV was popped() from child stack, so it's a part of some component
            // thus cannot be a candidate for separate component
            candidateForComponent[currentV] = false;

            for (int i = 0; i < vertices[currentV]->getDegree(); ++i) {
                int childV = vertices[currentV]->getIncidents()[i];
                if (!visited[childV]) {
                    unvisited.push(childV);
                }
            }
        }
        componentsCount++;
        componentVertices.push_back(c);
    }

    cout << componentsCount << endl;
}

void Graph::isBipartite() {
    bool is_red[verticesNum] = {};
    bool colored[verticesNum] = {};

    for (int startVertex : componentVertices) {
        // Process components
        bool visited[verticesNum] = {};
        // TODO: Implement custom stack
        stack<int> unvisited;
        unvisited.push(startVertex);
        is_red[startVertex] = true;
        colored[startVertex] = true;

        while (!unvisited.empty()) {
            int parentV = unvisited.top();
            unvisited.pop();

            if (visited[parentV])
                continue;

            visited[parentV] = true;


            for (int i = 0; i < vertices[parentV]->getDegree(); ++i) {
                int childV = vertices[parentV]->getIncidents()[i];
                if (!visited[childV]) {
                    if (colored[childV] && is_red[childV] == is_red[parentV]) {
                        cout << "F" << endl;
                        return;
                    }

                    unvisited.push(childV);
                    if (!colored[childV]) {
                        is_red[childV] = !is_red[parentV];
                        colored[childV] = true;
                    }
                }
            }
        }
    }

    for (int i = 0; i <= 1; i++) {
        for (int v1 = 0; v1 < verticesNum; v1++) {
            for (int v2 = 0; v2 < verticesNum; v2++) {
                if (v1 == v2)
                    continue;
                // can be optimised
                // checks if v2 is incident with v1, but does not remember it
                // so also checks if v1 is incident with v2
                if (is_red[v1] == is_red[v2] && vertices[v1]->isIncident(v2)) {
                    cout << "F" << endl;
                    return;
                }
            }
        }
    }
    cout << "T" << endl;
}

void Graph::eccentricity() {
    // TODO: Implement
    cout << '?' << endl;
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
