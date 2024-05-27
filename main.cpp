#include "Graph.h"

int main() {
    int graphNum = 0;
    int verticesNum = 0;
    int incidentNum = 0;
    int incidentIn = 0;
    cin >> graphNum;
    for (int i = 0; i < graphNum; i++) {
        // Process one graph
        cin >> verticesNum;
        Graph g(verticesNum);
        for (int vertex = 0; vertex < verticesNum; vertex++) {
            // Process one vertex
            cin >> incidentNum;
            g.addVertex(incidentNum);
            for (int incident = 0; incident < incidentNum; incident++) {
                // Process one incident vertex
                cin >> incidentIn;
                g.addIncident(vertex, incidentIn - 1);
            }
        }
        g.solve();
    }

    return 0;
}