#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED
#include <iostream>
#include <vector>
using namespace std;

#include "Agent.h"

class Simulation {
	private:
    	vector <Agent> agents;
        int max_agents;
    public:
    	int set_values(int);
    	int calculate_agents_repulsion();
    	Simulation(){};
    	~Simulation(){};
};

int Simulation::set_values(int m){
    max_agents = m;
    for (int agent_count=0; agent_count < max_agents; agent_count++){
        Agent agent;
        // agent.set_values(x,y,vx,vy,m,r);
        // agents.push_back(agent);
    }
}

int Simulation::calculate_agents_repulsion() {
    //figure out a way to include max agents in the 
	for (int agent_count = 0; agent_count < max_agents; agent_count++) {
		Agent agent = agents[agent_count];
		// agent.calculate_repulsion();
	}
}

#endif 
// SIMULATION_H_INCLUDED
