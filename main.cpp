#include <iostream>
#include <fstream>
#include <vector>
#include "Floor.h"
#include "Graph.h"
#include "Simulation.h"

using namespace std;

int main() {
    //initiate the floor
    Floor ground_floor;
    ground_floor.set_values("erb1_pixelValues.txt");
    // ground_floor.set_values("sample.txt");
    Graph g(ground_floor);
    g.set_floor();
    g.dijkstra();
    // preprocessing ends here //

    // runtime functions //
    int max_agents = 1;
    Simulation s;
    s.set_values(ground_floor, max_agents);
    // s.calculate_agents_repulsion();
    s.update_agents_position();
    // get the values
    // process the values -> solve the differential equation
    // write to text files
    return 0;
}