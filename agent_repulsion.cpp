#include <iostream>
#include <vector>
#include <math.h>
using namespace  std;

//#ifndef Agent_H
//#ifndef SIMULATION_H_INCLUDED_
//#define SIMULATION_H_INCLUDED_
#include "Agent.h"
#include "simulation.h"

class x_y { //vector or 2 dimensions
    public:
    float x;
    float y;
    };


int number_of_agents=250;
int main(){
Simulation s;
s.init_agents(number_of_agents);
for (int i=0; i<number_of_agents; i++){
    //int number_agents_near = num_agents_near (agents(i));
    for (int j=0; j<250, j++){

        float distance_bet_agents = float sqrtf((((agents(i).y - agents(j).y))*(agents(i).y - agents(j).y))+((agents(i).x - agents(j).x)*(agents(i).x - agents(j).x)));
        normal_tangent nij;
        x_y tangent_vector;
        x_y tangential_velocity;
        x_y Agent_repulsion_force;
        nij.x = ((agents(i).x - agents(j).x))/distance_bet_agents; // normalized vector pointing from i to j
        nij.y = ((agents(i).y - agents(j).y))/distance_bet_agents;

        tangent_vector.x = -nij.y; //tangent vector
        tangent_vector.y = nij.x;
        float sum_radius= agents(i).radius+agents(j).radius; //sum of the radius of the agents

        tangential_velocity.x = (agents(i).velocity.x-agents(j).x)*tangent_vector.x; //tangential velocity vector from i to j
        tangential_velocity.y = (agents(i).velocity.y-agents(j).y)*tangent_vector.y;

        int K1; //some constants whose value I don't know. Will need to ask Professor
        int K2;
        int A;
        int B;

        Agent_repulsion_force.x= Agent_repulsion_force.x+ ((A*exp((sum_radius-distance_bet_agents)/B)+(K1*9.81*(sum_radius-distance_bet_agents)))*nij.x + (K2*9.81*(sum_radius-distance_bet_agents)*tangential_velocity.x*tangent_vector.x);
        Agent_repulsion_force.y= Agent_repulsion_force.y+ ((A*exp((sum_radius-distance_bet_agents)/B)+(K1*9.81*(sum_radius-distance_bet_agents)))*nij.y + (K2*9.81*(sum_radius-distance_bet_agents)*tangential_velocity.y*tangent_vector.y);

    }
    return Agent_repululsion_force;
}
//#endif

