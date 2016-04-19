#include <iostream>

#include "Floor.h"
#include "Agent.h"

using namespace std;

int main() {
    cout << "Getting started? Good Luck!" << endl;

    //initiate the agents in their position
    //initiate the floor plan
    //let the agents evacuate
    int radius = 2;
    int mass = 80;
    Agent *agents[250];
    agents[1] = new Agent(radius, mass);
    agents[1]->position.x = 100;
    cout << agents[1]->position.x << endl;
    cout << agents[1]->position.y << endl;
    return 0;
}
