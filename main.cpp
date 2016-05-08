#include <iostream>
#include <fstream>
#include <vector>
#include "Floor.h"
#include "Graph.h"
#include "Simulation.h"

using namespace std;

int main() {
    //initiate the floor
    Floor f;
    // f.set_values("erb1_pixelValues.txt");
    f.set_values("sample.txt");
    Graph g;
    g.set_floor(f);
    g.dijkstra();

    // preprocessing ends here //

    // runtime functions //
    int max_agents = 250;
    Simulation s;
    s.set_values(max_agents);
    // s.calculate_agents_repulsion();

    // get the values
    // process the values -> solve the differential equation
    // write to text files
    return 0;
}