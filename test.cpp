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
    Graph g;
    g.set_floor(f);
    g.dijkstra();
    vector<float> dist = g.dijkstra();
    for(int i = 0; i < f.get_width()*f.get_height(); i++) {
    	cout << dist[i] << "\t";
    } 
    return 0;
}