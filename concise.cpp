#include <iostream>
#include <fstream>
#include <vector>
#include "Floor.h"
#include "concise.h"

using namespace std;

int main() {
    //initiate the floor
    Floor f;
    f.set_values("sample.txt");
    Graph g;
    g.set_floor(f);
    f.dummy();
    g.dijkstra();
    return 0;
}