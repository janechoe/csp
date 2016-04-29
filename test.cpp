#include <iostream>
#include <fstream>
#include <vector>
#include "Floor.h"
#include "test.h"

using namespace std;

#define width(f) {}
#define WEST(vertex, width) {vertex}
#define NORTH(vertex, width) {vertex-width}

int main() {
    //initiate the floor
    Floor f;
    f.set_values("sample.txt");
    cout << f.get_width() << endl; 
    cout << f.get_height() << endl;
    // cout << f.get_tile_color(0,0) << endl; 
    Graph g;
    g.set_values(f);
    return 0;
}