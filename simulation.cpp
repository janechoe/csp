#include <iostream>

#include "Floor.h"
#include "Agent.h"
#include "Simulation.h"

using namespace std;

struct {
    int *east;          // edge value = 1
    int *west;          // edge value = 1
    int *north;         // edge value = 1
    int *south;         // edge value = 1
    int *north_east;    // edge value = 1.41421356237
    int *south_east;    // edge value = 1.41421356237
    int *north_west;    // edge value = 1.41421356237
    int *south_west;    // edge value = 1.41421356237
} node;


int main() {
    cout << "Getting started? Good Luck!" << endl;
    // read the config file here
    // start by manually entering values for now.
    int image_width = 10, int image_height = 10;

    //declare all the pointers needed for the nodes
    vector<struct node> nodes;

    //define the nodes
    for(int i = 0; i <= width; i++) {
        for(int j = 0; j <= height; j++) {
            point = nodes.push_back(node());
            point.east = vector
        }
    }
    //connect the nodes



    /*
    int radius = 2;
    int mass = 80;

    Agent *agents[250];
    agents[1] = new Agent(radius, mass);

    cout << agents[1]->position.x << endl;
    cout << agents[1]->position.y << endl;
    */
    return 0;
}
