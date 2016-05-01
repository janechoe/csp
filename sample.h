#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Floor.h"
#include <limits>
#include <iostream>

#define inf std::numeric_limits<float>::infinity()

#define WIDTH 	(current_floor->get_width())
#define HEIGHT 	(current_floor->get_height())
#define AREA 	(WIDTH * HEIGHT)

#define ROW	(vertex/WIDTH)
#define COL (vertex%WIDTH)

#define SELF_COLOR (current_floor->get_tile_color(ROW, COL))
#define COLOR(r,c) (current_floor->get_tile_color(r,c))
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
		Floor *current_floor;
		int reset_graph();
		int update_graph(int);
		int generate_node(int, char);
		int connect_nodes() {
			return 0;
		};
		vector<int> prev_vertex; 
		vector<float> distance;
		//	NW	N   NE
		//	W 	i 	E
		// 	SW 	S 	SE
		//  graph[[W],[NW],[N],[NE],[E],[SW],[S],[SE],[i]]
		vector<vector<float> > graph;

	public:
		 int print_graph();
		 int set_floor(Floor *);
		 int find_route();
		 int dijkstra(); 
		 Graph() {};
		~Graph() {
			cout << "Deleting a graph object" << endl;
		};
};

int Graph::reset_graph() {
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < AREA; j++) {
			graph[i][j] = 0;
		}
	}
}

int Graph::set_floor(Floor *f) {
	current_floor = f;
	prev_vertex = vector<int> (WIDTH, -1);
	distance = vector<float> (WIDTH, inf );
	distance[0] = 0;
	prev_vertex[0] = 0;	
	//process a vector of 9xAREA
	for (int i = 0; i < 9; i++) {
		graph.push_back(vector<float>(AREA, 0) );
	}
	return 0;
}

int Graph::find_route(){
	for(int vertex = 0; vertex <= AREA-1; vertex++) {
		if (SELF_COLOR) {
			reset_graph();
			update_graph(vertex);
			// dijkstra();			
		}
	}
	reset_graph(); 
	cout << "voila" << endl;
	return 0;
};

int Graph::generate_node(int vertex, char dir) {
	cout << "generate_node called with vertex = " << vertex << endl; 
	// vector<float> node(AREA);
	graph[dir][WEST_VERTEX] 		= (WEST_IS_VALID) ? 1 : 0;
	graph[dir][NORTHWEST_VERTEX]	= (NORTHWEST_IS_VALID) ? 1.414 : 0;
	graph[dir][NORTH_VERTEX]		= (NORTH_IS_VALID) ? 1 : 0;	
	graph[dir][NORTHEAST_VERTEX]	= (NORTHEAST_IS_VALID) ? 1.414 : 0;
	graph[dir][EAST_VERTEX] 		= (EAST_IS_VALID) ? 1 : 0;
	graph[dir][SOUTHEAST_VERTEX]  = (SOUTHEAST_IS_VALID) ?  1.414 : 0;
	graph[dir][SOUTH_VERTEX] 		= (SOUTH_IS_VALID) ? 1 : 0;
	graph[dir][SOUTHWEST_VERTEX]  = (SOUTHWEST_IS_VALID) ? 1.414 : 0;
	return 0;
};

int Graph::update_graph(int vertex) {
	cout << endl << "update_graph called with vertex = " << vertex << " for row = "<< ROW << " and col = " << COL << endl;
	generate_node(vertex, CENTER);
	if (WEST_IS_VALID) generate_node(WEST_VERTEX, WEST);	
	if (NORTHWEST_IS_VALID) generate_node(NORTHWEST_VERTEX, NORTHWEST);
	if (NORTH_IS_VALID) generate_node(NORTH_VERTEX, NORTH);
	if (NORTHEAST_IS_VALID) generate_node(NORTHEAST_VERTEX, NORTHEAST);
	if (EAST_IS_VALID) generate_node(EAST_VERTEX, EAST);
	if (SOUTHEAST_IS_VALID) generate_node(SOUTHEAST_VERTEX, SOUTHEAST);
	if (SOUTH_IS_VALID)  generate_node(SOUTH_VERTEX, SOUTH);
	if (SOUTHWEST_IS_VALID) generate_node(SOUTHWEST_VERTEX, SOUTHWEST);


	return 0;
}

int Graph::dijkstra() {
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

#endif


