#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Floor.h"
#include <limits>
#include <iostream>

#define inf std::numeric_limits<int>::infinity()

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

using namespace std;

class Graph {

	private: 
		Floor current_floor;
		int generate_nodes();
		int connect_nodes() {
			return 0;
		};
		struct Node
		{
			char west;			//can alternatively be -+1 to indicate east/west
			char northwest;
			char north;
			char northeast;
			char east;
			char southeast;
			char south;
			char southwest;
		};
		vector<vector<struct Node> > nodes; 

	public:
		 int set_values(Floor);
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
};

int Graph::set_values(Floor f) {
	current_floor = f;
	int last_vertex = WIDTH * HEIGHT - 1;
	for (int vertex = 0; vertex <= last_vertex; vertex++) {
		// vertices.push_back(vector<float> (last_vertex, 0) );
		cout << COLOR(ROW,COL) << ((COL==(WIDTH-1)) ? "\n" : " ");
	} cout << endl;	

	// generate_nodes();
	// connect_nodes();
	return 0;
}
int Graph::generate_nodes() {
	int last_vertex = AREA-1;
	for (int vertex = 0; vertex <= last_vertex; vertex++){
		// int row = vertex / floor_p.get_width();
		// int col = vertex % floor_p.get_width();
		// west 	 (vertex)	= west_is_valid(vertex) ? 1 : 0; 
		// northwest(vertex) 	= northwest_is_valid(vertex) ? 1.414 : 0; 
		// north 	 (vertex) 	= north_is_valid(vertex) ? 1 : 0; 
		// northeast(vertex) 	= northeast_is_valid(vertex) ? 1.414 : 0; 
		// east 	 (vertex) 	= east_is_valid(vertex) ? 1 : 0;
		// southeast(vertex) 	= southeast_is_valid(vertex) ? 1.414 : 0; 
		// west 	 (vertex) 	= south_is_valid(vertex) ? 1 : 0; 
		// southwest(vertex) 	= southwest_is_valid(vertex) ? 1.414 : 0; 
	}
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
