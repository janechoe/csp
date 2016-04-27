#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Floor.h"
#include <limits>
#define inf std::numeric_limits<int>::infinity()
using namespace std;

class Graph{

	private:
		// Floor *floor_p;
		int width;
		int height;
		struct Node {
			char color;
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
		vector< vector<struct Node*> > nodes_p; 
		// vector<struct Node*> nodes_p;
		int generate_nodes() {
			for(int row = 0; row < floor_p->height; row++) {
				for(int col = 0; col < floor_p->width; col++) {
					Node node;
					node.color = (row + col)%32000;
					if (node.color != 0) {	//code-rem color for black = 0 for now.
						
					}
					nodes_p[row][col] = &node;
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
		Graph(w, h) : width{w}, height{h}{
			generate_nodes();
			connect_nodes();
		};
};
#endif
