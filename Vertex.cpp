#include "Vertex.h"

Vertex::Vertex(int incNum) {
    incidentNum = incNum;
    incidentV = new int[incNum];
    for (int i = 0; i < incidentNum; i++) {
        incidentV[i] = -1;
    }
};

Vertex::~Vertex() {
    delete[] incidentV;
}

void Vertex::addIncident(int inc) {
    if (free_inc_id >= incidentNum) {
        throw std::invalid_argument("free_inc_id exceeded incidentNum");
    }
    incidentV[free_inc_id++] = inc;
}

void Vertex::print() {
    for (int i = 0; i < incidentNum; i++)
        cout << incidentV[i] << " ";
}