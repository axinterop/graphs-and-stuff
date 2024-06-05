#include "Graph.h"

bool descending(int a, int b) { return a > b; }

typedef struct {
    int vertex;
    int degree;
    int saturation;
} VDS;

bool descendingVertexDegree(const VDS a, const VDS b) {
    if (a.degree == b.degree)
        return a.vertex <= b.vertex;
    return a.degree > b.degree;
}

bool descendingVertexDegreeSaturation(const VDS a, const VDS b) {
    if (a.saturation == b.saturation) {
        if (a.degree == b.degree)
            return a.vertex < b.vertex;
        return a.degree > b.degree;
    }
    return a.saturation > b.saturation;
}

template<typename T, typename Compare>
void merge(Vector<T> &arr, int start, int mid, int end, Compare comp) {
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

template<typename T, typename Compare>
void mergeSort(Vector<T> &arr, int start, int end, Compare comp) {
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
}

Vertex &Graph::operator[](int index) {
    if (index < 0 || index >= verticesNum) {
        cout << "Index out of bounds" << endl;
        exit(1);
    }
    return *vertices[index];
}

void Graph::addVertex(int n, int incNum) {
    if (size >= verticesNum) {
        throw std::invalid_argument("size exceeded verticesNum");
    }
    vertices[size++] = new Vertex(n, incNum);
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
//    cout << "?" << endl;
    eccentricity();
//    cout << "?" << endl;
    isPlanar();
//    cout << "?" << endl;
    colorGreedy();
//    cout << "?" << endl;
    colorLF();
//    cout << "?" << endl;
    colorSLF();
//    cout << "?" << endl;
    numberOfC4();
//    cout << "?" << endl;
    numberOfComplementEdges();
//    cout << "?" << endl;
}

void Graph::degreeSequence() {
    Vector<int> degrees(verticesNum);
    for (int v = 0; v < verticesNum; v++)
        degrees.push_back(vertices[v]->getDegree());
    mergeSort(degrees, 0, verticesNum - 1, descending);
    for (int v = 0; v < verticesNum; v++)
        printf("%d ", degrees[v]);
    printf("\n");
}

void Graph::numberOfComponents() {
    Vector<bool> candidateForComponent(verticesNum, true);
    Vector<bool> visited(verticesNum, false);
    int componentsCount = 0;

    for (int startVertex = 0; startVertex < verticesNum; startVertex++) {
        if (!visited[startVertex] && candidateForComponent[startVertex]) {
            dfs(startVertex, visited, candidateForComponent);
            componentsCount++;
            componentVertices.push_back(startVertex);
        }
    }

    printf("%d\n", componentsCount);
}

void Graph::isBipartite() {
    Vector<bool> is_red(verticesNum, false);
    Vector<bool> colorIsSet(verticesNum, false);

    for (int startVertex = 0; startVertex < verticesNum; startVertex++) {
        // Process components
        if (colorIsSet[startVertex])
            continue;

        Queue unvisited(verticesNum);
        unvisited.enqueue(startVertex);
        is_red[startVertex] = true;
        colorIsSet[startVertex] = true;

        while (!unvisited.isEmpty()) {
            int parentV = unvisited.peek();
            unvisited.dequeue();

            for (int childV: *vertices[parentV]) {
                if (colorIsSet[childV]) {
                    if (is_red[childV] == is_red[parentV]) {
                        printf("F\n");
                        return;
                    }
                } else {
                    is_red[childV] = !is_red[parentV];
                    colorIsSet[childV] = true;
                    unvisited.enqueue(childV);
                }
            }
        }
    }

    printf("T\n");
}

void Graph::eccentricity() {
    int counter = 0;

    for (int startVertex = 0; startVertex < verticesNum; startVertex++) {
        if (vertices[startVertex]->getDegree() == 0) {
            printf("0 ");
            continue;
        }

        Vector<int> distance(verticesNum, -1);
        Queue unvisited(verticesNum);
        unvisited.enqueue(startVertex);
        distance[startVertex] = 0;
        counter++;
        int max = 0;

        while (!unvisited.isEmpty()) {
            if (counter == size) {
                while (!unvisited.isEmpty())
                    unvisited.dequeue();
                break;
            }
            int parentV = unvisited.peek();
            unvisited.dequeue();

            for (int childV: *vertices[parentV]) {
                if (distance[childV] == -1) {
                    distance[childV] = distance[parentV] + 1;
                    unvisited.enqueue(childV);
                    counter++;
                    if (distance[childV] > max)
                        max = distance[childV];
                }
            }
        }
        printf("%d ", max);
        counter = 0;
    }
    printf("\n");
}

void Graph::isPlanar() {
    // TODO: Implement
    cout << '?' << endl;
}


void Graph::colorGreedy() {
    Vector<int> color(verticesNum, 0);
    Vector<bool> colorOccupied(verticesNum, false);
    color[0] = 1;
    printf("%d ", color[0]);
    for (int parentV = 1; parentV < verticesNum; parentV++) {
        for (int childV: *vertices[parentV]) {
            if (color[childV] != 0)
                colorOccupied[color[childV]] = true;
        }

        int potentialColor;
        for (potentialColor = 1; potentialColor < verticesNum + 1; potentialColor++) {
            if (!colorOccupied[potentialColor])
                break;
        }

        color[parentV] = potentialColor;
        printf("%d ", potentialColor);

        for (int childV: *vertices[parentV]) {
            colorOccupied[color[childV]] = false;
        }
    }

    printf("\n");
}


void Graph::colorLF() {
    Vector<VDS> vd(verticesNum);
    for (int v = 0; v < verticesNum; v++) {
        vd[v].vertex = v;
        vd[v].degree = vertices[v]->getDegree();
    }
    mergeSort(vd, 0, verticesNum - 1, descendingVertexDegree);

    Vector<int> color(verticesNum, 0);
    color[vd[0].vertex] = 1;
    Vector<bool> colorOccupied(verticesNum, false);

    int parentV;
    for (int vIndex = 1; vIndex < verticesNum; vIndex++) {
        parentV = vd[vIndex].vertex;
        for (int childV: *vertices[parentV]) {
            colorOccupied[color[childV]] = true;
        }

        int potentialColor;
        for (potentialColor = 1; potentialColor < verticesNum + 1; potentialColor++)
            if (!colorOccupied[potentialColor]) break;
        color[parentV] = potentialColor;

        for (int childV: *vertices[parentV]) {
            if (color[childV] != 0)
                colorOccupied[color[childV]] = false;
        }
    }

    for (int v = 0; v < verticesNum; v++)
        printf("%d ", color[v]);
    printf("\n");
}

void Graph::colorSLF() {
    // TODO: Implement
    cout << '?' << endl;
}

void Graph::numberOfC4() {
    // TODO: Implement
    cout << '?' << endl;
}

#define ulli unsigned long long int

void Graph::numberOfComplementEdges() {
    ulli allVertices = verticesNum;
    ulli allEdgesComplement = allVertices * (allVertices - 1) / 2;
    ulli allEdges = 0;
    for (int v = 0; v < verticesNum; v++)
        allEdges += vertices[v]->getDegree();
    allEdges /= 2;
    printf("%llu\n", allEdgesComplement - allEdges);
}

void Graph::dfs(int startVertex, Vector<bool> &visited, Vector<bool> &candidateForComponent) {
    visited[startVertex] = true;
    candidateForComponent[startVertex] = false;

    for (int i = 0; i < vertices[startVertex]->getDegree(); ++i) {
        int childV = vertices[startVertex]->getIncidents()[i];
        if (!visited[childV]) {
            dfs(childV, visited, candidateForComponent);
        }
    }
}
