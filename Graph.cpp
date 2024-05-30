#include "Graph.h"

bool descending(int a, int b) { return a > b; }

bool descendingVertex(const Vertex *a, const Vertex *b) {
    if (a->getDegree() == b->getDegree())
        return a->getNum() <= b->getNum();
    return a->getDegree() > b->getDegree();
}

bool descendingVertexSaturation(const Vertex *a, const Vertex *b) {
    if (a->getSaturation() == b->getSaturation()) {
        if (a->getDegree() == b->getDegree())
            return a->getNum() < b->getNum();
        return a->getDegree() > b->getDegree();
    }
    return a->getSaturation() > b->getSaturation();
}

template <typename T, typename Compare>
void merge(Vector<T>& arr, int start, int mid, int end, Compare comp) {
    int left = start, right = mid + 1;
    Vector<T> temp(end - start + 1);
    int k = 0;

    while (left <= mid && right <= end) {
        if (comp(arr[left], arr[right])) {
            temp[k++] = arr[left++];
        } else {
            temp[k++] = arr[right++];
        }
    }

    while (left <= mid) {
        temp[k++] = arr[left++];
    }

    while (right <= end) {
        temp[k++] = arr[right++];
    }

    for (int i = 0; i < k; i++) {
        arr[start + i] = temp[i];
    }
}

template <typename T, typename Compare>
void mergeSort(Vector<T>& arr, int start, int end, Compare comp) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(arr, start, mid, comp); // Sort left sub-array
        mergeSort(arr, mid + 1, end, comp); // Sort right sub-array
        merge(arr, start, mid, end, comp); // Merge sorted sub-arrays
    }
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

void Graph::addVertex(int n, int incNum) {
    if (free_v_id >= verticesNum) {
        throw std::invalid_argument("free_v_id exceeded verticesNum");
    }
    vertices[free_v_id++] = new Vertex(n, incNum);
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
    Vector<int> degrees(verticesNum);
    for (int v = 0; v < verticesNum; v++)
        degrees.push_back(vertices[v]->getDegree());
    mergeSort(degrees, 0, verticesNum - 1, descending);
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
        Stack unvisited;
        unvisited.push(startVertex);

        while (!unvisited.isEmpty()) {
            int currentV = unvisited.peek();
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
    bool colorIsSet[verticesNum] = {};

    for (int startVertex: componentVertices) {
        // Process components
        bool visited[verticesNum] = {};
        Stack unvisited;
        unvisited.push(startVertex);
        is_red[startVertex] = true;
        colorIsSet[startVertex] = true;

        while (!unvisited.isEmpty()) {
            int parentV = unvisited.peek();
            unvisited.pop();

            if (visited[parentV])
                continue;
            visited[parentV] = true;

            for (int i = 0; i < vertices[parentV]->getDegree(); ++i) {
                int childV = vertices[parentV]->getIncidents()[i];
                if (!visited[childV]) {
                    if (colorIsSet[childV] && is_red[childV] == is_red[parentV]) {
                        cout << "F" << endl;
                        return;
                    }
                    if (!colorIsSet[childV]) {
                        is_red[childV] = !is_red[parentV];
                        colorIsSet[childV] = true;
                    }
                    unvisited.push(childV);
                }
            }
        }
    }

    for (int v1 = 0; v1 < verticesNum; v1++) {
        for (int v2 = 0; v2 < verticesNum; v2++) {
            if (v1 == v2)
                continue;
            // can be optimised
            // checks if v2 is incident with v1, but
            // also checks if v1 is incident with v2
            if (is_red[v1] == is_red[v2] && vertices[v1]->isIncident(v2)) {
                cout << "F" << endl;
                return;
            }
        }
    }
    cout << "T" << endl;
}

void Graph::eccentricity() {
    for (int startVertex = 0; startVertex < verticesNum; startVertex++) {
        // Process components
        int distance[verticesNum] = {};
        bool distanceIsSet[verticesNum] = {};
        Queue unvisited;
        unvisited.enqueue(startVertex);
        distance[startVertex] = 0;
        distanceIsSet[startVertex] = true;

        while (!unvisited.isEmpty()) {
            int parentV = unvisited.peek();
            unvisited.dequeue();
            for (int i = 0; i < vertices[parentV]->getDegree(); ++i) {
                int childV = vertices[parentV]->getIncidents()[i];
                if (!distanceIsSet[childV]) {
                    distance[childV] = distance[parentV] + 1;
                    distanceIsSet[childV] = true;
                    unvisited.enqueue(childV);
                }
            }
        }

        int max = -1;
        for (auto d: distance) {
            if (d > max) max = d;
        }
        cout << max << " ";
    }
    cout << endl;
}

void Graph::isPlanar() {
    // TODO: Implement
    cout << '?' << endl;
}

void Graph::colorGreedy() {
    int color[verticesNum] = {};
    color[0] = 1;
    for (int parentV = 1; parentV < verticesNum; parentV++) {
        bool colorOccupied[verticesNum] = {};
        for (int i = 0; i < vertices[parentV]->getDegree(); i++) {
            int childV = vertices[parentV]->getIncidents()[i];
            colorOccupied[color[childV]] = true;
        }
        for (int potenticalColor = 1; potenticalColor < verticesNum + 1; potenticalColor++) {
            if (!colorOccupied[potenticalColor]) {
                color[parentV] = potenticalColor;
                break;
            }
        }
    }
    for (int v = 0; v < verticesNum; v++) {
        cout << color[v] << " ";
    }

    cout << endl;
}

void Graph::colorLF() {
    Vector<Vertex*> verticesDesc(verticesNum);
    for (int v = 0; v < verticesNum; v++)
        verticesDesc[v] = vertices[v];
    mergeSort(verticesDesc, 0, verticesNum - 1, descendingVertex);

    int color[verticesNum] = {};
    color[verticesDesc[0]->getNum()] = 1;

    for (int vIndex = 1; vIndex < verticesNum; vIndex++) {
        int parentV = verticesDesc[vIndex]->getNum();
        bool colorOccupied[verticesNum] = {};
        for (int i = 0; i < vertices[parentV]->getDegree(); i++) {
            int childV = vertices[parentV]->getIncidents()[i];
            colorOccupied[color[childV]] = true;
        }
        for (int potenticalColor = 1; potenticalColor < verticesNum + 1; potenticalColor++) {
            if (!colorOccupied[potenticalColor]) {
                color[parentV] = potenticalColor;
                break;
            }
        }
    }

    for (int v = 0; v < verticesNum; v++)
        cout << color[v] << " ";
    cout << endl;

//    delete[] verticesDesc;
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
