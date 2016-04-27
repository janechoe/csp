#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Floor.h"
#include <limits>

using namespace std;

class Graph : public Floor {

	private:
		Floor* floor_p;
		struct Node {
			int distance;
		    Node* east;
		    Node* west;
		    Node* north;
		    Node* south;
		    Node* north_east;
		    Node* south_east;
		    Node* north_west;
		    Node* south_west;
		};
		vector<struct Node*> nodes_p;
		int generate_nodes() {
			for(int row = 0; row < floor_plan->height; row++) {
				for(int col = 0; col < floor_plan->width; col++) {
					if (floor_plan->tiles_p[row][col]-> color = 0) {	//code-rem
						Node node;
						node.distance = inf;
						nodes_p.push_back(&node);
					}
				}
			} 
		};
		int connect_nodes() {
			//connect each node to all neighbours
			//check for boundary conditions
			//add a supernode for assembly point
			return 0;
		};

	public:
		Graph(Floor* f) : floor_p{f}{
			generate_nodes();
			connect_nodes();
		};
};
#endif
