#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

#include "Agent.h"
#include "Floor.h"

class Simulation {
	private:
    	vector <Agent> agents;
        int max_agents;
        Floor current_floor;
    public:
    	int set_values(Floor&, int);
    	int calculate_agents_repulsion();
        int initiate_agent_position_files();
        int update_agents_position();
    	Simulation(){};
    	~Simulation(){};
};

int Simulation::set_values(Floor& f, int m){
    current_floor = f;
    max_agents = m;
    for (int agent_count=0; agent_count < max_agents; agent_count++){
        Agent agent;
        int x =  rand() % current_floor.width;
        int y =  rand() % current_floor.height;
        // cout << agent_count << x << " " << y << endl;
        while ( (current_floor.get_tile(y, x).color != 3) && (current_floor.get_tile(y,x).agent_number == -1) ) { //get tile expects row, col
            x = rand() % current_floor.width;
            y = rand() % current_floor.height;
            // cout << agent_count << " " << x << " " << y << endl;
        }
        cout << agent_count << " " << x << " " << y << endl;
        agent.set_values(current_floor, x, y, 0, 0, 85, 3);
        agents.push_back(agent);
        current_floor.tiles[y][x].agent_number = agent_count;
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
        file_name = "rendering/agent" + to_string(agent_count) + ".csv";
        agent_file.open(file_name, ios::out);
        agent_file.close();
    }
}

int Simulation::update_agents_position() {
    
    initiate_agent_position_files();
    
    int x; int y;
    string file_name;
    vector <ofstream> agent_files (max_agents); 
    for (int agent_count = 0; agent_count < max_agents; agent_count++) {
        file_name = "rendering/agent" + to_string(agent_count) + ".csv";
        agent_files[agent_count].open(file_name, ios::app);
    }

    bool active_agent_exists = 1;
    while (active_agent_exists) {
        active_agent_exists = 0;
        for (int agent_count = 0; agent_count < max_agents; agent_count++) {
            // Agent agent = agents[agent_count];    
            if (agents[agent_count].active) {
                agents[agent_count].update_acceleration();
                agents[agent_count].update_velocity();
                agents[agent_count].update_position();
                //write the position to a file;
                    file_name = "rendering/agent" + to_string(agent_count) + ".csv";
                    agent_files[agent_count] << agents[agent_count].position.col << "," << agents[agent_count].position.row << endl;
                // check if the agent has reached the source
                    if ( agents[agent_count].position.color == 1 ) {
                        agents[agent_count].active = 0;
                        continue;
                    } else {
                            active_agent_exists = 1;
                    }
            }
        }
    }
    return 0;
}

#endif 
// SIMULATION_H_INCLUDED
