#ifndef PROJECT3_VERTEX_H
#define PROJECT3_VERTEX_H

#include <stdexcept>
#include <iostream>
using namespace std;


class Vertex {
private:
    int *incidentV;
    int free_inc_id = 0;
    int incidentNum;
public:
    Vertex(): incidentV(nullptr), incidentNum(0) {};
    explicit Vertex(int incNum);
    ~Vertex();

    void addIncident(int inc);
    bool isIncident(int key);
    void print();

    int getDegree() { return incidentNum; };
    const int* getIncidents() { return incidentV; };
};



#endif //PROJECT3_VERTEX_H
