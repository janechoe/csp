#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Floor.h"
#include <limits>
#include <iostream>
#include <math.h>
#include <algorithm>

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
		vector<int>   prev_vertex; 
		vector<float> distance_from_source;
		vector<bool>  was_processed;
		vector<int>	  neighbours = vector<int> (9,-1);
		vector<float> distance_to_neighbour = vector<float> (9);
		vector<float> queue;
		int queue_size;
		float last_minimum_distance = 0;
		int start_count = 0;
		int update_neighbours_info(int);
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
	queue.push_back(0);
	queue_size = 1;
	distance_from_source[0] = 0;
	prev_vertex[0] = 0;	
	return 0;
}



int Graph::dijkstra() {
	int last_start = 0;
	for( int iteration = 0; iteration <= queue_size; iteration++ ) {
		cout << " iteration : " << iteration << endl;
		int starting_vertex = queue[iteration];	
		int row = starting_vertex/WIDTH;
		int col = starting_vertex%WIDTH;
		if (COLOR(row, col)) {
			was_processed[starting_vertex] = true;
			update_neighbours_info(starting_vertex);
			for(int direction = 1; direction <= 8; direction++) {
				if ( (neighbours[direction] != -1) && !was_processed[neighbours[direction]] 
					&& ( (distance_from_source[starting_vertex]+distance_to_neighbour[direction]) < distance_from_source[neighbours[direction]]) ) {
					distance_from_source[neighbours[direction]] = distance_from_source[starting_vertex] + distance_to_neighbour[direction];
					prev_vertex[neighbours[direction]] = starting_vertex;
					int location = -1;
					for(int i = iteration; i < queue_size; i++) {
						if (queue[i] == neighbours[direction]) {
							location = i; 
							break;
						}
					}
					if (location == -1) {
						queue.push_back(neighbours[direction]);
						++queue_size;
						location = queue_size;
					}
					for(int i = queue_size-1; i > 0; i--) {
						if ( distance_from_source[queue[i-1]] < distance_from_source[queue[i]]) {
							break;
						} else {
							swap(queue[i-1], queue[i]);
						}
					}
				}		
			}
		}
	}
	see_stuff();
	return 0;
};


int Graph::update_neighbours_info(int vertex) {
	neighbours[0] = vertex;
	if (WEST_IS_VALID ) {
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
    // the maze
    for (int row = 0 ; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            cout << current_floor.get_tile_color(row, col) << "\t";
        } cout << "\v" << endl;
    } cout << endl;

	// vertex numbers
    for (int row = 0 ; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            cout << (row * WIDTH + col) << "\t";
        } cout << "\v" << endl;
    } cout << endl;

	// prev_vertex
    for (int row = 0 ; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            cout << prev_vertex[(row * WIDTH + col)] << "\t";
        } cout << "\v" << endl;
    } cout << endl;

	// distance from source
    for (int row = 0 ; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            cout << distance_from_source[(row * WIDTH + col)] << "\t";
        } cout << "\v" << endl;
    } cout << endl;

	// traversal pattern
    // for (int row = 0 ; row < HEIGHT; row++) {
    //     for (int col = 0; col < WIDTH; col++) {
    //         // cout << prev_vertex[row * WIDTH + col] << "\t";
    //         cout << was_processed[row * WIDTH + col] << "\t";
    //     } cout << "\v" << endl;
    // } cout << endl;

}
#endif
