#ifndef PROJECT3_VERTEX_H
#define PROJECT3_VERTEX_H

#include <stdexcept>
#include <iostream>
using namespace std;


class Vertex {
private:
    int num;
    int *incidentV;
    int free_inc_id = 0;
    int incidentNum;
    int saturation = 0;
public:
    Vertex(): num(-1), incidentV(nullptr), incidentNum(0) {};
    explicit Vertex(int n, int incNum);
    ~Vertex();

    void addIncident(int inc);
    bool isIncident(int key);
    void print();

    int getDegree() const { return incidentNum; };
    int getNum() const { return num; }
    const int* getIncidents() { return incidentV; };
    void setSaturation(int s) { saturation = s; };
    int getSaturation() const { return saturation; };

    Vertex& operator=(const Vertex& other);
    int operator[](int index);

    int* begin() { return incidentV; }
    const int* begin() const { return incidentV; }
    int* end() { return incidentV + incidentNum; }
    const int* end() const { return incidentV + incidentNum; }
};



#endif //PROJECT3_VERTEX_H
