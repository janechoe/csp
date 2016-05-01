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

#define SELF_COLOR (current_floor.tiles[ROW][COL].color)
#define COLOR(r,c) (current_floor.tiles[r][c].color)
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
		void print_graph();
		int reset_graph();
		int update_graph(int);
		vector<float> generate_node(int);
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
	cout << "voila" << endl;
	return 0;
};

vector<float> Graph::generate_node(int vertex) {
	cout << "generate_node called with vertex = " << vertex << endl; 
	vector<float> node(AREA);
	cout << "doint WEST_VERTEX" << endl;
	node[WEST_VERTEX] 		= (WEST_IS_VALID) ? 1 : 0;
	cout << "doint NORTHWEST_VERTEX" << endl;
	node[NORTHWEST_VERTEX]	= (NORTHWEST_IS_VALID) ? 1.414 : 0;
	cout << "doint NORTH_VERTEX" << endl;
	node[NORTH_VERTEX]		= (NORTH_IS_VALID) ? 1 : 0;	
	cout << "doint NORTHEAST_VERTEX" << endl;
	node[NORTHEAST_VERTEX]	= (NORTHEAST_IS_VALID) ? 1.414 : 0;
	cout << "doint EAST_VERTEX" << endl;
	node[EAST_VERTEX] 		= (EAST_IS_VALID) ? 1 : 0;
	cout << "doint SOUTHEAST_VERTEX" << endl;
	node[SOUTHEAST_VERTEX]  = (SOUTHEAST_IS_VALID) ?  1.414 : 0;
	cout << "doint SOUTH_VERTEX" << endl;
	node[SOUTH_VERTEX] 		= (SOUTH_IS_VALID) ? 1 : 0;
	cout << "doint SOUTHWEST_VERTEX" << endl;
	node[SOUTHWEST_VERTEX]  = (SOUTHWEST_IS_VALID) ? 1.414 : 0;
	cout << "Printing node for the vertex = " << vertex  << "\t"; 
	for (int i = 0; i <= 8; i++) {
		 cout << node[i] << "\t";
	}; cout << endl ;
	cout << &node << endl;
	return node;
};

int Graph::update_graph(int vertex) {
	cout << endl << "update_graph called with vertex = " << vertex << " for row = "<< ROW << " and col = " << COL << endl;
	//print the content of graph;
	print_graph();
							graph[vertex]	=generate_node(vertex);
	print_graph();							
	if (WEST_IS_VALID)		graph[WEST]		=generate_node(WEST_VERTEX);	
	print_graph();
	if (NORTHWEST_IS_VALID) graph[NORTHWEST]=generate_node(NORTHWEST_VERTEX);
	print_graph();
	if (NORTH_IS_VALID) 	graph[NORTH]	=generate_node(NORTH_VERTEX);
	print_graph();
	if (NORTHEAST_IS_VALID) graph[NORTHEAST]=generate_node(NORTHEAST_VERTEX);
	print_graph();
	if (EAST_IS_VALID) 		graph[EAST]		=generate_node(EAST_VERTEX);
	print_graph();
	if (SOUTHEAST_IS_VALID) graph[SOUTHEAST]=generate_node(SOUTHEAST_VERTEX);
	print_graph();
	// cout << endl << endl << "before south" << endl << endl;

	if (SOUTH_IS_VALID) 	graph[SOUTH]	=generate_node(SOUTH_VERTEX);
	print_graph();
	// cout << endl << endl << "after south " << graph.size() << endl << endl;
	if (SOUTHWEST_IS_VALID) graph[SOUTHWEST]=generate_node(SOUTHWEST_VERTEX);
	print_graph();

	return 0;
}

int Graph::dijkstra() {
	return 0;
};

void Graph::print_graph() {
	//Print the content of graph
	cout << "printing graph" << endl;
	for(int i = 0; i <= 8; i++) {
		for (int j = 0; j < AREA; j++) {
			cout << graph[i][j] << "\t";
		} cout << endl;
	}cout << endl;	
}


#endif

