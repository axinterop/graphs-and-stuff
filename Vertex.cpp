#include "Vertex.h"

Vertex::Vertex(int n, int incNum) {
    num = n;
    incidentNum = incNum;
    incidentV = new int[incNum];
    for (int i = 0; i < incidentNum; i++) {
        incidentV[i] = -1;
    }
}

Vertex::~Vertex() {
    delete[] incidentV;
}

void Vertex::addIncident(int inc) {
    if (free_inc_id >= incidentNum) {
        throw std::invalid_argument("free_inc_id exceeded incidentNum");
    }
    incidentV[free_inc_id++] = inc;
}

bool Vertex::isIncident(int key) {
    for (int i = 0; i < incidentNum; i++) {
        if (incidentV[i] == key)
            return true;
    }
    return false;
}

void Vertex::print() {
    for (int i = 0; i < incidentNum; i++)
        cout << incidentV[i] << " ";
}

Vertex& Vertex::operator=(const Vertex& other) {
    // Check for self-assignment
    if (this != &other) {
        // Release existing resources
        delete[] incidentV;

        // Copy data from 'other' object
        num = other.num;
        incidentNum = other.incidentNum;
        incidentV = new int[incidentNum];
        free_inc_id = other.free_inc_id;
        for (int i = 0; i < incidentNum; i++) {
            incidentV[i] = other.incidentV[i];
        }
    }

    return *this;
}

int Vertex::operator[](int index) {
    return incidentV[index];
}
