#include <iostream>
#include <fstream>
#include <vector>
#include "Floor.h"
#include "sample.h"

using namespace std;

int main() {
    //initiate the floor
    Floor f;
    f.set_values("sample.txt");
    Graph g;
    // g.set_floor(f);
    f.dummy();
    // g.find_route();
    return 0;
}