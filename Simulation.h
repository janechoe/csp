#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#include "Agent.h"
#include "Floor.h"

class Simulation {
	private:
    	vector <Agent> agents;
        int max_agents;
        Floor current_floor;
    public:
    	int set_values(Floor, int);
    	int calculate_agents_repulsion();
        int initiate_agent_position_files();
        int update_agents_position();
    	Simulation(){};
    	~Simulation(){};
};

int Simulation::set_values(Floor f, int m){
    current_floor = f;
    max_agents = m;
    for (int agent_count=0; agent_count < max_agents; agent_count++){
        Agent agent;
        // agent.set_values(x,y,vx,vy,m,r);
        agent.set_values(current_floor, 7, 7, 0, 0, 85, 3);
        agents.push_back(agent);
    } 
}

int Simulation::calculate_agents_repulsion() {
    //figure out a way to include max agents in the 
	for (int agent_count = 0; agent_count < max_agents; agent_count++) {
		Agent agent = agents[agent_count];
		// agent.calculate_repulsion();
	}
}

int Simulation::initiate_agent_position_files() {
    string file_name;
    for (int agent_count = 0; agent_count < max_agents; agent_count++) {
        ofstream agent_file;
        file_name = "agent" + to_string(agent_count) + ".csv";
        agent_file.open(file_name, ios::out);
        agent_file.close();
    }
}

int Simulation::update_agents_position() {
    int x; int y;
    string file_name;
    vector <ofstream> agent_files (max_agents); 
    for (int agent_count = 0; agent_count < max_agents; agent_count++) {
        file_name = "agent" + to_string(agent_count) + ".csv";
        agent_files[agent_count].open(file_name, ios::app);
    }

    bool active_agent_exists = 1;
    // while (active_agent_exists) {
        active_agent_exists = 0;
        for (int agent_count = 0; agent_count < max_agents; agent_count++) {
            Agent agent = agents[agent_count];
            if (agent.active) {
                active_agent_exists = 1;
                agent.update_position();
                //write the position to a file;
                    file_name = "agent" + to_string(agent_count) + ".csv";
                    agent_files[agent_count] << agent.position.col << "," << agent.position.row << endl;
                // check if the agent has reached the source
                    if ( (agent.position.row == 0) && (agent.position.col == 0) ) {
                        agent.active = 0;
                        continue;
                    }
                agent.update_velocity();
                agent.update_acceleration();
            }
        }
    // }
    return 0;
}

#endif 
// SIMULATION_H_INCLUDED
