#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED
#include <iostream>
#include <vector>
using namespace std;

#include "Agent.h"

class Simulation {
	private:
    	vector <Agent> agents;
    public:
    	int init_agents(int);
    	Simulation();
    	~Simulation();
};

int init_agents(max_agents){
    for (int i=0; i < max_agents; i++){
        Agent single_agent;
        single_agent.set_values(x,y,vx,vy,m,r);
        agents.push_back(agent);
    }
}

#endif 
// SIMULATION_H_INCLUDED
