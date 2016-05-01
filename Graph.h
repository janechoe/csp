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

#define WEST_IS_VALID  (COL > 0 && COLOR(ROW,COL-1)  )
#define NORTH_IS_VALID (ROW > 0 && COLOR(ROW-1,COL) )
#define EAST_IS_VALID  (COL < WIDTH-1 && COLOR(ROW,COL+1)  )
#define SOUTH_IS_VALID (ROW < HEIGHT-1 && COLOR(ROW+1,COL) )
#define NORTHWEST_IS_VALID ( ROW > 0 && COL > 0 && COLOR(ROW-1,COL-1) )
#define NORTHEAST_IS_VALID ( ROW > 0 && COL < WIDTH-1  && COLOR(ROW-1,COL+1) )
#define SOUTHEAST_IS_VALID ( ROW < HEIGHT-1 && COL < WIDTH-1 && COLOR(ROW+1,COL+1) )
#define SOUTHWEST_IS_VALID ( ROW < HEIGHT-1 && COL > 0 && COLOR(ROW+1,COL-1) )

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
		int pick_starting_vertex();
		vector<int>   prev_vertex; 
		vector<float> distance_from_source;
		vector<bool>  was_processed;
		vector<int>	  neighbours;
		vector<float> distance_to_neighbour;
		int update_neighbours(int);	
		int update_distance_to_neighbours(int);
		void see_stuff();

	public:
		 int set_floor(Floor);
		 int dijkstra(); 
		 Graph() {};
		~Graph() {};
};

int Graph::set_floor(Floor f) {
	current_floor = f;
	prev_vertex = vector<int> (AREA, -1);
	distance_from_source = vector<float> (AREA, inf);
	was_processed = vector<bool> (AREA, false);
	distance_from_source[0] = 0;
	prev_vertex[0] = 0;	
	neighbours = vector<int> (9,-1);
	distance_to_neighbour = vector<float> (9);
	return 0;
}



int Graph::dijkstra() {
	for( int vertex = 0; vertex < AREA-1; vertex++ ) {
		if (SELF_COLOR) {
			int starting_vertex = pick_starting_vertex();
			was_processed[starting_vertex] = true;
			update_neighbours(starting_vertex);
			update_distance_to_neighbours(starting_vertex);
			for(int direction = 1; direction <= 8; direction++) {
				if ( (neighbours[direction] != -1) && !was_processed[neighbours[direction]] 
					&& ( (distance_from_source[starting_vertex]+distance_to_neighbour[direction]) <= /* rem probable error */ distance_from_source[neighbours[direction]]) ) {
					distance_from_source[neighbours[direction]] = distance_from_source[starting_vertex] + distance_to_neighbour[direction];
					prev_vertex[neighbours[direction]] = starting_vertex;					
				}		
			}
		}
	}
	see_stuff();
	return 0;
};

//pick the minimum distance vertex from the list of vertices not yet processed
int Graph::pick_starting_vertex() {
	float minimum_distance = inf;
	int minimum_distance_vertex;
	for (int vertex = 0; vertex < AREA-1; vertex++) {
		if ( SELF_COLOR && (was_processed[vertex] == false) && (distance_from_source[vertex] < minimum_distance) ) {
			minimum_distance = distance_from_source[vertex];
			minimum_distance_vertex = vertex;
		}
	}
	was_processed[minimum_distance_vertex] = true;
	return minimum_distance_vertex;
}

int Graph::update_neighbours(int vertex) {
	neighbours[0] = vertex;
	neighbours[WEST] 		= (WEST_IS_VALID) 		? WEST_VERTEX 		: -1;	
	neighbours[NORTHWEST] 	= (NORTHWEST_IS_VALID)  ? NORTHWEST_VERTEX 	: -1;
	neighbours[NORTH] 		= (NORTH_IS_VALID) 		? NORTH_VERTEX 		: -1;
	neighbours[NORTHEAST] 	= (NORTHEAST_IS_VALID)  ? NORTHEAST_VERTEX	: -1;
	neighbours[EAST] 		= (EAST_IS_VALID) 		? EAST_VERTEX		: -1;
	neighbours[SOUTHEAST]	= (SOUTHEAST_IS_VALID) 	? SOUTHEAST_VERTEX 	: -1;
	neighbours[SOUTH] 		= (SOUTH_IS_VALID) 		? SOUTH_VERTEX 		: -1;
	neighbours[SOUTHWEST] 	= (SOUTHWEST_IS_VALID) 	? SOUTHWEST_VERTEX 	: -1;
	return 0;
}

int Graph::update_distance_to_neighbours(int vertex) {
	distance_to_neighbour[WEST] 	 = (WEST_IS_VALID) 		? 1 : 0;
	distance_to_neighbour[NORTHWEST] = (NORTHWEST_IS_VALID) ? 1.414 : 0;
	distance_to_neighbour[NORTH] 	 = (NORTH_IS_VALID) 	? 1 : 0;
	distance_to_neighbour[NORTHEAST] = (NORTHEAST_IS_VALID) ? 1.414 : 0;
	distance_to_neighbour[EAST] 	 = (EAST_IS_VALID) 		? 1 : 0;
	distance_to_neighbour[SOUTHEAST] = (SOUTHEAST_IS_VALID) ? 1.414 : 0;
	distance_to_neighbour[SOUTH] 	 = (SOUTH_IS_VALID) 	? 1 : 0;
	distance_to_neighbour[SOUTHWEST] = (SOUTHWEST_IS_VALID) ? 1.414 : 0;
	return 0;
};

void Graph::see_stuff() {
	cout << endl;
    for (int row = 0 ; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            cout << (row * WIDTH + col) << "\t";
        } cout << "\v" << endl;
    } cout << endl;
    for (int row = 0 ; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            cout << prev_vertex[row * WIDTH + col] << "\t";
        } cout << "\v" << endl;
    } cout << endl;

}
#endif


