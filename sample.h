#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Floor.h"
#include <limits>
#include <iostream>

#define inf std::numeric_limits<float>::infinity()

#define WIDTH 	(current_floor.width)
#define HEIGHT 	(current_floor.height)
#define AREA 	(WIDTH * HEIGHT)

#define ROW	(vertex/WIDTH)
#define COL (vertex%WIDTH)

#define SELF_COLOR (current_floor.get_tile_color(ROW, COL))
#define COLOR(r,c) (current_floor.get_tile_color(r,c))
// #define GET_MACRO(_1, _2, COLOR,...) COLOR
// #define COLOR(...) GET_MACRO(__VA_ARGS__, COLOR2, COLOR1)(__VA_ARGS__)
//http://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments

/* row and col is doing maths multiple times
** replace by local variables when possible
** on a side note, probably optimized by compilers
*/
#define WEST_IS_VALID  (COL > 0 && COLOR(ROW,COL-1)  )
#define NORTH_IS_VALID (ROW > 0 && COLOR(ROW-1,COL) )
#define EAST_IS_VALID  (COL < WIDTH-1 && COLOR(ROW,COL+1)  )
#define SOUTH_IS_VALID (ROW < HEIGHT-1 && COLOR(ROW+1,COL) )
#define NORTHWEST_IS_VALID ( NORTH_IS_VALID && WEST_IS_VALID && COLOR(ROW-1,COL-1) )
#define NORTHEAST_IS_VALID ( NORTH_IS_VALID && EAST_IS_VALID && COLOR(ROW-1,COL+1) )
#define SOUTHEAST_IS_VALID ( SOUTH_IS_VALID && EAST_IS_VALID && COLOR(ROW+1,COL+1) )
#define SOUTHWEST_IS_VALID ( SOUTH_IS_VALID && WEST_IS_VALID && COLOR(ROW+1,COL-1) )

#define WEST_VERTEX  ( vertex-1 )
#define NORTH_VERTEX ( vertex-WIDTH )
#define EAST_VERTEX  ( vertex+1 )
#define SOUTH_VERTEX ( vertex+WIDTH )
#define NORTHWEST_VERTEX ( NORTH_VERTEX-1 )
#define NORTHEAST_VERTEX ( NORTH_VERTEX+1 )
#define SOUTHEAST_VERTEX ( SOUTH_VERTEX+1 )
#define SOUTHWEST_VERTEX ( SOUTH_VERTEX-1 )

#define CENTER		0
#define WEST 		1
#define NORTHWEST 	2
#define NORTH 		3
#define NORTHEAST 	4
#define EAST 		5
#define SOUTHEAST 	6
#define SOUTH 		7
#define SOUTHWEST 	8



using namespace std;

class Graph {

	private: 
		Floor current_floor;
		int reset_graph();
		int update_graph(int);
		int generate_node(int, char);
		int pick_starting_vertex();
		int connect_nodes() {
			return 0;
		};
		vector<int>   prev_vertex; 
		vector<float> distance_from_source;
		vector<bool>  was_processed;
		vector<int>	  neighbours;
		vector<float> distance_to_neighbour;
		int update_neighbours(int);	
		//	NW	N   NE
		//	W 	i 	E
		// 	SW 	S 	SE
		//  graph[[SELF],[W],[NW],[N],[NE],[E],[SW],[S],[SE],[i]]
		vector<vector<float> > graph;

	public:
		 int print_graph();
		 int set_floor(Floor);
		 int find_route();
		 int dijkstra(); 
		 Graph() {};
		~Graph() {};
};

int Graph::reset_graph() {
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < AREA; j++) {
			graph[i][j] = 0;
		}
	}
}

int Graph::set_floor(Floor f) {
	current_floor = f;
	prev_vertex = vector<int> (AREA, -1);
	distance_from_source = vector<float> (AREA, inf);
	was_processed = vector<bool> (AREA, false);
	distance_from_source[0] = 0;
	prev_vertex[0] = 0;	
	//process a vector of 9xAREA
	for (int i = 0; i < 9; i++) {
		graph.push_back(vector<float>(AREA, 0) );
	}
	neighbours = vector<int> (9,-1);
	distance_to_neighbour = vector<float> (9);
	for(int direction = 0; direction < 9; direction++) {
		distance_to_neighbour = (direction%2) ? 1 : 1.414;
	}
	
	return 0;
}

int Graph::find_route(){
	// for(int vertex = 0; vertex <= AREA-1; vertex++) {
	// 	// cout << vertex << "\t";
	// 	// if ( ((vertex+1) % WIDTH) == 0 ) {
	// 	// 	cout << "\n\v";
	// 	// }
	// 	if (SELF_COLOR) {
	// 		reset_graph();
	// 		update_graph(vertex);
			dijkstra();			
	// 	}
	// } cout << endl;
	return 0;
};

int Graph::generate_node(int vertex, char dir) {
	if (WEST_IS_VALID) 		graph[dir][WEST_VERTEX] 	 = 1;
	if (NORTHWEST_IS_VALID) graph[dir][NORTHWEST_VERTEX] = 1.414;
	if (NORTH_IS_VALID) 	graph[dir][NORTH_VERTEX] 	 = 1;
	if (NORTHEAST_IS_VALID) graph[dir][NORTHEAST_VERTEX] = 1.414;
	if (EAST_IS_VALID)		graph[dir][EAST_VERTEX] 	 = 1;
	if (SOUTHEAST_IS_VALID) graph[dir][SOUTHEAST_VERTEX] = 1.414;
	if (SOUTH_IS_VALID)		graph[dir][SOUTH_VERTEX] 	 = 1;
	if (SOUTHWEST_IS_VALID)	graph[dir][SOUTHWEST_VERTEX] = 1.414;
	return 0;
};

int Graph::update_graph(int vertex) {
	generate_node(vertex, CENTER);
	if (WEST_IS_VALID) 		generate_node(WEST_VERTEX, WEST);	
	if (NORTHWEST_IS_VALID) generate_node(NORTHWEST_VERTEX, NORTHWEST);
	if (NORTH_IS_VALID) 	generate_node(NORTH_VERTEX, NORTH);
	if (NORTHEAST_IS_VALID) generate_node(NORTHEAST_VERTEX, NORTHEAST);
	if (EAST_IS_VALID) 		generate_node(EAST_VERTEX, EAST);
	if (SOUTHEAST_IS_VALID) generate_node(SOUTHEAST_VERTEX, SOUTHEAST);
	if (SOUTH_IS_VALID)  	generate_node(SOUTH_VERTEX, SOUTH);
	if (SOUTHWEST_IS_VALID) generate_node(SOUTHWEST_VERTEX, SOUTHWEST);
	return 0;
}

int Graph::dijkstra() {
	for( int count = 0; count < AREA; count++ ) {
		update_neighbours(count);
		// int starting_vertex = pick_starting_vertex();
		//update the distance for the neighbours
		// for(int vertex = 0; vertex < AREA; vertex++) {
		// 	update_graph();
		// 	update_neighbours();
		// 	if ( !was_processed[vertex] && graph[starting_vertex][vertex] && (distance_from_source[starting_vertex] != inf) && (distance_from_source[starting_vertex] + graph[starting_vertex][vertex] < distance_from_source[vertex]) ) {
		// 		distance_from_source[vertex] = distance_from_source[starting_vertex] + graph[starting_vertex][vertex];
		// 	}
		// }
	}
	return 0;
};

int Graph::print_graph() {
	//Print the content of graph
	cout << "printing graph" << endl;
	for(int i = 0; i <= 8; i++) {
		for (int j = 0; j < AREA; j++) {
			cout << graph[i][j] << "\t";
		} cout << endl;
	}cout << endl;
	return 0;	
}

//pick the minimum distance vertex from the list of vertices not yet processed
int Graph::pick_starting_vertex() {
	int minimum_distance = inf;
	int minimum_distance_vertex;
	for (int vertex = 0; vertex < AREA; vertex++) {
		if ( (was_processed[vertex] == false) && (distance_from_source[vertex] < minimum_distance) ) {
			cout << "\tcondition true" << endl;
			minimum_distance = distance_from_source[vertex];
			minimum_distance_vertex = vertex;
		}
	}
	cout << minimum_distance_vertex << endl;
	was_processed[minimum_distance_vertex] = true;
	return minimum_distance_vertex;
}

int Graph::update_neighbours(int vertex) {
	cout << "update_neighbours called with vertex " << vertex << endl;
	neighbours[0] = 0;
	if (WEST_IS_VALID) 		neighbours[WEST] 		= WEST_VERTEX;	
	if (NORTHWEST_IS_VALID) neighbours[NORTHWEST] 	= NORTHWEST_VERTEX;
	if (NORTH_IS_VALID) 	neighbours[NORTH] 		= NORTH_VERTEX;
	if (NORTHEAST_IS_VALID) neighbours[NORTHEAST] 	= NORTHEAST_VERTEX;
	if (EAST_IS_VALID) 		neighbours[EAST] 		= EAST_VERTEX;
	if (SOUTHEAST_IS_VALID) neighbours[SOUTHEAST]	= SOUTHEAST_VERTEX;
	if (SOUTH_IS_VALID)  	neighbours[SOUTH] 		= SOUTH_VERTEX;
	if (SOUTHWEST_IS_VALID) neighbours[SOUTHWEST] 	= SOUTHWEST_VERTEX;
	return 0;
}
#endif


