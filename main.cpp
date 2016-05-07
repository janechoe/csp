#include <iostream>
#include <fstream>
#include <vector>
#include "Floor.h"
#include "Graph.h"

using namespace std;

int main() {
    //initiate the floor
    Floor f;
    // f.set_values("erb1_pixelValues.txt");
    f.set_values("sample.txt");
    Graph g;
    g.set_floor(f);
    g.dijkstra();
    return 0;
}