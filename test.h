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

#define COLOR0 (current_floor.tiles[r][c].color)
#define COLOR2(r,c) (current_floor.tiles[r][c].color)
#define GET_MACRO(_0, _2, COLOR,...) COLOR
#define COLOR(...) GET_MACRO(__VA_ARGS__, COLOR2, COLOR0)(__VA_ARGS__)
//http://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments

/* row and col is doing maths multiple times
** replace by local variables when possible
** on a side note, probably optimized by compilers
*/
#define WEST_IS_VALID  ((COL != 0) && COLOR(ROW,COL-1)  )
#define NORTH_IS_VALID (ROW != 0 && COLOR(ROW-1,COL) != 0 )
#define EAST_IS_VALID  (COL != WIDTH-1 && COLOR(ROW,COL+1) != 0  )
#define SOUTH_IS_VALID (ROW != HEIGHT-1 && COLOR(ROW+1,COL) != 0 )
#define NORTHWEST_IS_VALID ( NORTH_IS_VALID && WEST_IS_VALID && COLOR(ROW-1,COL-1) != 0)
#define NORTHEAST_IS_VALID ( NORTH_IS_VALID && EAST_IS_VALID && COLOR(ROW-1,COL+1) != 0)
#define SOUTHEAST_IS_VALID ( SOUTH_IS_VALID && EAST_IS_VALID && COLOR(ROW+1,COL+1) != 0)
#define SOUTHWEST_IS_VALID ( SOUTH_IS_VALID && WEST_IS_VALID && COLOR(ROW+1,COL-1) != 0)

#define WEST_VERTEX  ( vertex-1 )
#define NORTH_VERTEX ( vertex-WIDTH )
#define EAST_VERTEX  ( vertex+1 )
#define SOUTH_VERTEX ( vertex+WIDTH )
#define NORTHWEST_VERTEX ( NORTH_VERTEX-1 )
#define NORTHEAST_VERTEX ( NORTH_VERTEX+1 )
#define SOUTHEAST_VERTEX ( SOUTH_VERTEX+1 )
#define SOUTHWEST_VERTEX ( SOUTH_VERTEX-1 )

using namespace std;

class Graph {

	private: 
		Floor current_floor;
		int generate_nodes(int);
		int connect_nodes() {
			return 0;
		};
		// struct Node
		// {
		// 	char west;			//can alternatively be -+1 to indicate east/west
		// 	char northwest;
		// 	char north;
		// 	char northeast;
		// 	char east;
		// 	char southeast;
		// 	char south;
		// 	char southwest;
		// };
		vector<int> prev_vertex; 
		vector<float> distance;
		vector<vector<float> > graph; 

	public:
		 int set_floor(Floor);
		 vector<float> dijkstra();
		 Graph() {};
		~Graph() {};
};

int Graph::set_floor(Floor f) {
	current_floor = f;
	prev_vertex = vector<float> (WIDTH);
	distance = vector<float> (WIDTH, infinity);
	distance[0] = 0;
	prev_vertex[0] = 0;	
	// // generate_nodes();
	// // connect_nodes();
	return 0;
}
int Graph::generate_nodes(int vertex) {
	// if (WEST_IS_VALID) nodes[WEST_VERTEX]=1;
	// if (NORTH_IS_VALID) nodes[NORTH_VERTEX]=1;
	// if (EAST_IS_VALID) nodes[EAST_VERTEX]=1;
	// if (SOUTH_IS_VALID) nodes[SOUTH_VERTEX]=1;
	// if (NORTHWEST_IS_VALID) nodes[NORTHWEST_VERTEX]=1.414;
	// if (NORTHWEST_IS_VALID) nodes[NORTHWEST_VERTEX]=1.414;
	// if (SOUTHEAST_IS_VALID) nodes[SOUTHEAST_VERTEX]=1.414;
	// if (SOUTHWEST_IS_VALID) nodes[SOUTHWEST_VERTEX]=1.414;
	return 0;
};
#endif

vector<float> Graph::dijkstra() {
	vector<vector<float> > graph;
	for(int i = 0; i < 8;i++) {
		graph.push_back(vector<float> (AREA) );
	}

	// int last_vertex = AREA-1;
	// for(int vertex = 0; vertex <= last_vertex; vertex++){
	// 	generate_graph(vertex);
	// }; 
	return dist; 
};
