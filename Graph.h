#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Floor.h"
#include <limits>
#define inf std::numeric_limits<int>::infinity()

using namespace std;

Floor Graph(const Floor &current_floor) {

	private: 
		Floor *floor_p;
		vector<vector<float> > vertices; 
		int generate_nodes();
		int connect_nodes() {
			//connect each node to all neighbours
			//check for boundary conditions
			//add a supernode for assembly point
			return 0;
		};

	public:
		 int set_values(Floor *);
		 Graph() {};
		~Graph() {};

	private:
		int west(int);
		int northwest(int);
		int north(int);
		int northeast(int);
		int east(int);
		int southeast(int);
		int south(int);
		int southwest(int);

		bool west_is_valid(int);
		bool northwest_is_valid(int);
		bool north_is_valid(int);
		bool northeast_is_valid(int);
		bool east_is_valid(int);
		bool southeast_is_valid(int);
		bool south_is_valid(int);
		bool southwest_is_valid(int);
};

int Graph::set_values(Floor *f) {
	floor_p = f;
	int last_vertex = f->get_area()-1;
	for (int vertex = 0; vertex <= last_vertex; vertex++) {
		vertices.push_back(vector<float> (last_vertex, 0) );
	}
	//generate_nodes();
	// connect_nodes();
	return 0;
}
int Graph::generate_nodes() {
	int last_vertex = floor_p->get_area()-1;
	for (int vertex = 0; vertex <= last_vertex; vertex++){
		int row = vertex / floor_p->get_width();
		int col = vertex % floor_p->get_width();
		// west 	 (vertex)	= west_is_valid(vertex) ? 1 : 0; 
		// northwest(vertex) 	= northwest_is_valid(vertex) ? 1.414 : 0; 
		// north 	 (vertex) 	= north_is_valid(vertex) ? 1 : 0; 
		// northeast(vertex) 	= northeast_is_valid(vertex) ? 1.414 : 0; 
		// east 	 (vertex) 	= east_is_valid(vertex) ? 1 : 0;
		// southeast(vertex) 	= southeast_is_valid(vertex) ? 1.414 : 0; 
		// west 	 (vertex) 	= south_is_valid(vertex) ? 1 : 0; 
		// southwest(vertex) 	= southwest_is_valid(vertex) ? 1.414 : 0; 
	}
	// for(int row = 0; row < floor_p->height; row++) {
	// 	for(int col = 0; col < floor_p->width; col++) {
	// 		Node node;
	// 		node.color = floor_p->get_tile_color(row, color);
	// 		if (node.color != 0) {	//code-rem color for black = 0 for now.
				
	// 		}
	// 		nodes_p[row][col] = &node;
	// 	}
	// } 
};
#endif

int Graph::west(int vertex){

	return 0;
};
int Graph::northwest(int vertex){
	return 0;
};
int Graph::north(int vertex){
	return 0;
};
int Graph::northeast(int vertex){
	return 0;
};
int Graph::east(int vertex){
	return 0;
};
int Graph::southeast(int vertex){
	return 0;
};
int Graph::south(int vertex){
	return 0;
};
int Graph::southwest(int vertex){
	return 0;
};

bool Graph::west_is_valid(int vertex){
	// if (vertex > 0 && (vertex % width) != 0)
	return false;
};
bool Graph::northwest_is_valid(int vertex){
	return 0;
};
bool Graph::north_is_valid(int vertex){
	return 0;
};
bool Graph::northeast_is_valid(int vertex){
	return 0;
};
bool Graph::east_is_valid(int vertex){
	return 0;
};
bool Graph::southeast_is_valid(int vertex){
	return 0;
};
bool Graph::south_is_valid(int vertex){
	return 0;
};
bool Graph::southwest_is_valid(int vertex){
	return 0;
};
