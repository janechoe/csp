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
		vector<int>	  neighbours = vector<int> (9,-1);
		vector<float> distance_to_neighbour = vector<float> (9);
		float last_minimum_distance = 0;
		int last_diagonal_vertex;
		int update_last_diagonal_vertex();
		int update_last_diagonal_vertex_neighbours();
		int update_neighbours_info(int);
		void see_stuff();
		int testing = 0;
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
	// neighbours = vector<int> (9,-1);
	// distance_to_neighbour = vector<float> (9);
	return 0;
}



int Graph::dijkstra() {
	int last_start = 0;
	for( int vertex = 0; vertex < AREA-1; vertex++ ) {
		// see_stuff();
		if (SELF_COLOR) {
			int starting_vertex = pick_starting_vertex();
			cout << "last_diagonal_vertex" << last_diagonal_vertex << endl;
			cout << "starting_vertex " << starting_vertex << endl << endl;
			update_neighbours_info(starting_vertex);
			for(int direction = 1; direction <= 8; direction++) {
				if ( (neighbours[direction] != -1) && !was_processed[neighbours[direction]] 
					&& ( (distance_from_source[starting_vertex]+distance_to_neighbour[direction]) <= /* rem probable error */ distance_from_source[neighbours[direction]]) ) {
					distance_from_source[neighbours[direction]] = distance_from_source[starting_vertex] + distance_to_neighbour[direction];
					prev_vertex[neighbours[direction]] = starting_vertex;	
				}		
			}
		}
		update_last_diagonal_vertex();
		update_last_diagonal_vertex_neighbours();	
	}
	see_stuff();
	return 0;
};

int Graph::update_last_diagonal_vertex() {

	for (int vertex = last_diagonal_vertex%WIDTH ; vertex <=last_diagonal_vertex; vertex+=WIDTH) {
		if ( SELF_COLOR && (was_processed[vertex] == false) ) {
			return 0;
		}
	}

	for (int vertex = (last_diagonal_vertex/WIDTH)*WIDTH ; vertex < last_diagonal_vertex; vertex++) {
		if ( SELF_COLOR && (was_processed[vertex] == false) ) { 
			return 0;
		}
	}

	if (last_diagonal_vertex/WIDTH == HEIGHT-1) {
		last_diagonal_vertex++;
	} else {
		last_diagonal_vertex += (WIDTH+1);		
	}
	update_neighbours_info(last_diagonal_vertex);
	return 0;
}

//pick the minimum distance vertex from the list of vertices not yet processed
int Graph::pick_starting_vertex() {
	float minimum_distance = inf;
	int minimum_distance_vertex = 0;
	vector<bool> processed_diagonal_vertex;

	for (int vertex = last_diagonal_vertex%WIDTH; vertex < last_diagonal_vertex; vertex+=WIDTH) {
		if (last_diagonal_vertex==44) {
			cout << vertex << "+" << was_processed[vertex]<<"+"<<distance_from_source[vertex]<<"+"<<minimum_distance<< endl;
		}
		if ( SELF_COLOR && (was_processed[vertex] == false) && (distance_from_source[vertex] < minimum_distance) ) {
			minimum_distance = distance_from_source[vertex];
			minimum_distance_vertex = vertex;
		}
	}
	for (int vertex = (last_diagonal_vertex/WIDTH)*WIDTH ; vertex <= last_diagonal_vertex; vertex++) {
		if (last_diagonal_vertex==44) {
			cout << vertex << "+" << was_processed[vertex] << endl;
		}		
		if ( SELF_COLOR && (was_processed[vertex] == false) && (distance_from_source[vertex] < minimum_distance) ) {
			minimum_distance = distance_from_source[vertex];
			minimum_distance_vertex = vertex;
		}
	}
	was_processed[minimum_distance_vertex] = true;
	last_minimum_distance = distance_from_source[minimum_distance_vertex];
	// if (minimum_distance_vertex==42) exit(-1);
	return minimum_distance_vertex;
}

int Graph::update_neighbours_info(int vertex) {
	neighbours[0] = vertex;
	if (WEST_IS_VALID) {
		neighbours[WEST] = WEST_VERTEX;
		distance_to_neighbour[WEST]	= 1; 
	} else {
		neighbours[WEST] = -1;
		distance_to_neighbour[WEST] = 0;
	}
	if (NORTHWEST_IS_VALID) {
		neighbours[NORTHWEST] = NORTHWEST_VERTEX;
		distance_to_neighbour[NORTHWEST]= 1.414; 
	} else {
		neighbours[NORTHWEST] = -1;
		distance_to_neighbour[NORTHWEST] = 0;
	}
	if (NORTH_IS_VALID) {
		neighbours[NORTH] = NORTH_VERTEX;
		distance_to_neighbour[NORTH]	= 1; 
	} else {
		neighbours[NORTH] = -1;
		distance_to_neighbour[NORTH] = 0;
	}
	if (NORTHEAST_IS_VALID) {
		neighbours[NORTHEAST] = NORTHEAST_VERTEX;
		distance_to_neighbour[NORTHEAST]	= 1.414; 
	} else {
		neighbours[NORTHEAST] = -1;
		distance_to_neighbour[NORTHEAST] = 0;
	}
	if (EAST_IS_VALID) {
		neighbours[EAST] = EAST_VERTEX;
		distance_to_neighbour[EAST]	= 1; 
	} else {
		neighbours[EAST] = -1;
		distance_to_neighbour[EAST] = 0;
	}
	if (SOUTHEAST_IS_VALID) {
		neighbours[SOUTHEAST] = SOUTHEAST_VERTEX;
		distance_to_neighbour[SOUTHEAST]= 1.414; 
	} else {
		neighbours[SOUTHEAST] = -1;
		distance_to_neighbour[SOUTHEAST] = 0;
	}
	if (SOUTH_IS_VALID) {
		neighbours[SOUTH] = SOUTH_VERTEX;
		distance_to_neighbour[SOUTH]	= 1; 
	} else {
		neighbours[SOUTH] = -1;
		distance_to_neighbour[SOUTH] = 0;
	}
	if (SOUTHWEST_IS_VALID) {
		neighbours[SOUTHWEST] = SOUTHWEST_VERTEX;
		distance_to_neighbour[SOUTHWEST]	= 1.414; 
	} else {
		neighbours[SOUTHWEST] = -1;
		distance_to_neighbour[SOUTHWEST] = 0;
	}
	return 0;
}

void Graph::see_stuff() {
    // for (int row = 0 ; row < HEIGHT; row++) {
    //     for (int col = 0; col < WIDTH; col++) {
    //         cout << current_floor.get_tile_color(row, col) << "\t";
    //     } cout << "\v" << endl;
    // } cout << endl;

    // for (int row = 0 ; row < HEIGHT; row++) {
    //     for (int col = 0; col < WIDTH; col++) {
    //         cout << (row * WIDTH + col) << "\t";
    //     } cout << "\v" << endl;
    // } cout << endl;

    // for (int row = 0 ; row < HEIGHT; row++) {
    //     for (int col = 0; col < WIDTH; col++) {
    //         cout << prev_vertex[(row * WIDTH + col)] << "\t";
    //     } cout << "\v" << endl;
    // } cout << endl;

    // for (int row = 0 ; row < HEIGHT; row++) {
    //     for (int col = 0; col < WIDTH; col++) {
    //         cout << distance_from_source[(row * WIDTH + col)] << "\t";
    //     } cout << "\v" << endl;
    // } cout << endl;

	// traversal pattern
	cout << "last_diagonal_vertex: " << last_diagonal_vertex << endl;
    for (int row = 0 ; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            // cout << prev_vertex[row * WIDTH + col] << "\t";
            cout << was_processed[row * WIDTH + col] << "\t";
        } cout << "\v" << endl;
    } cout << endl;

}
#endif
