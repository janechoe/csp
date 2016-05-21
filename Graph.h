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

#define WEST_IS_VALID  (col > 0 && COLOR(row,col-1) )
#define NORTH_IS_VALID (row > 0 && COLOR(row-1,col) )
#define EAST_IS_VALID  (col < WIDTH-1 && COLOR(row,col+1)  )
#define SOUTH_IS_VALID (row < HEIGHT-1 && COLOR(row+1,col) )
#define NORTHWEST_IS_VALID ( row > 0 && col > 0 && COLOR(row-1,col-1) )
#define NORTHEAST_IS_VALID ( row > 0 && col < WIDTH-1  && COLOR(row-1,col+1) )
#define SOUTHEAST_IS_VALID ( row < HEIGHT-1 && col < WIDTH-1 && COLOR(row+1,col+1) )
#define SOUTHWEST_IS_VALID ( row < HEIGHT-1 && col > 0 && COLOR(row+1,col-1) )

#define WEST_EXISTS  ((col > 0 ))
#define NORTH_EXISTS ((row > 0 ))
#define EAST_EXISTS  ((col < WIDTH-1))
#define SOUTH_EXISTS ((row < HEIGHT-1))
#define NORTHWEST_EXISTS (( row > 0 && col > 0 ))
#define NORTHEAST_EXISTS (( row > 0 && col < WIDTH-1))
#define SOUTHEAST_EXISTS (( row < HEIGHT-1 && col < WIDTH-1))
#define SOUTHWEST_EXISTS (( row < HEIGHT-1 && col > 0 ))

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
		Floor &current_floor;
		vector<int>   prev_vertex; 
		vector<float> distance_from_source;
		vector<bool>  was_processed;
		vector<int>	  neighbours = vector<int> (9,-1);
		vector<float> distance_to_neighbour = vector<float> (9);
		vector<float> queue;
		int queue_size;
		float last_minimum_distance = 0;
		int start_count = 0;
		int update_neighbours_info(int 	/* 	neighbours[direction] */);
		int update_desired_direction(int /* neighbours[direction]*/);
		int process_wall_force(int, int);
		int update_queue(int, int);
		void see_stuff();

	public:
		 int set_floor();
		 int dijkstra(); 
		 Graph(Floor &f):current_floor(f) {};
		~Graph() {};
};

int Graph::set_floor() {
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
		// cout << " iteration : " << iteration << endl;
		int starting_vertex = queue[iteration];	
		int row = starting_vertex/WIDTH;
		int col = starting_vertex%WIDTH;
		was_processed[starting_vertex] = true;
		update_neighbours_info(starting_vertex);
		process_wall_force(row, col);
		// current_floor.normalize_wall_force(row, col);
		for(int direction = WEST; direction <= SOUTHWEST; direction++) {
			if ( (neighbours[direction] != -1) && !was_processed[neighbours[direction]] 
				&& ( (distance_from_source[starting_vertex]+distance_to_neighbour[direction]) < distance_from_source[neighbours[direction]]) ) {
				distance_from_source[neighbours[direction]] = distance_from_source[starting_vertex] + distance_to_neighbour[direction];
				
				// uncomment to get the vertex number of previous vertex 
				// on the shortest path
				prev_vertex[neighbours[direction]] = starting_vertex;
				
				// update the desired direction for an agent
				// on a tile to the tile closer to the exit 
				// on the shortest path
				update_desired_direction(direction);

				//update the queue with the processed vertex
				update_queue(iteration, neighbours[direction]);
			}		
		}
	}
	// see_stuff();
	return 0;
};

int Graph::update_queue(int iteration, int neighbour) {
	int location = -1;
	for(int i = iteration; i < queue_size; i++) {
		if (queue[i] == neighbour) {
			location = i; 
			break;
		}
	}
	if (location == -1) {
		queue.push_back(neighbour);
		++queue_size;
		location = queue_size;
	} else {
		for(int i = queue_size-1; i > 0; i--) {
			if ( distance_from_source[queue[i-1]] < distance_from_source[queue[i]]) {
				break;
			} else {
				swap(queue[i-1], queue[i]);
			}
		}
	}
}


int Graph::update_neighbours_info(int vertex) {
	// neighbours[0] = vertex;
	int row = vertex/current_floor.width;
	int col = vertex%current_floor.width;
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

int Graph::process_wall_force(int row, int col) {
	if (COLOR(row, col)) {
		if (WEST_EXISTS 	 &&	!COLOR(row 	, col-1) ) 	current_floor.set_wall_force(row, col, 1, 0);
		if (NORTHWEST_EXISTS && !COLOR(row-1, col-1) ) 	current_floor.set_wall_force(row, col, 1, 1);
		if (NORTH_EXISTS 	 && !COLOR(row-1, col  ) ) 	current_floor.set_wall_force(row, col, 0, 1);
		if (NORTHEAST_EXISTS && !COLOR(row-1, col+1) ) 	current_floor.set_wall_force(row, col,-1, 1);
		if (EAST_EXISTS 	 &&	!COLOR(row  , col+1) ) 	current_floor.set_wall_force(row, col,-1, 0);
		if (SOUTHEAST_EXISTS && !COLOR(row+1, col+1) ) 	current_floor.set_wall_force(row, col,-1,-1);
		if (SOUTH_EXISTS 	 && !COLOR(row+1, col  ) ) 	current_floor.set_wall_force(row, col, 0,-1);
		if (SOUTHWEST_EXISTS && !COLOR(row+1, col-1) ) 	current_floor.set_wall_force(row, col, 1,-1);
		// current_floor.normalize_wall_force(row, col);
	};
	
	return 0;
}


int Graph::update_desired_direction(int direction) {
	switch (direction) {
		case WEST 	  : current_floor.set_direction(neighbours[direction], 1, 0); break;
		case NORTHWEST: current_floor.set_direction(neighbours[direction], 1, 1); break; 
		case NORTH 	  : current_floor.set_direction(neighbours[direction], 0, 1); break; 
		case NORTHEAST: current_floor.set_direction(neighbours[direction],-1, 1); break; 
		case EAST 	  : current_floor.set_direction(neighbours[direction],-1, 0); break; 
		case SOUTHEAST: current_floor.set_direction(neighbours[direction],-1,-1); break; 
		case SOUTH 	  : current_floor.set_direction(neighbours[direction], 0,-1); break; 
		case SOUTHWEST: current_floor.set_direction(neighbours[direction], 1,-1); break; 
		default : ;
	}
}

void Graph::see_stuff() {
    cout << "the maze" << endl;
    for (int row = 0 ; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            cout << current_floor.get_tile_color(row, col) << "\t";
        } cout << "\v" << endl;
    } cout << endl;

    cout << "tiles properties" << endl;
    for (int row = 0 ; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            cout << "(" << current_floor.get_tile(row,col).row << "," << current_floor.get_tile(row,col).col << ")"<< "\t";
        } cout << "\v" << endl;
    } cout << endl;

	// cout << " vertex numbers " << endl;
 //    for (int row = 0 ; row < HEIGHT; row++) {
 //        for (int col = 0; col < WIDTH; col++) {
 //            cout << (row * WIDTH + col) << "\t";
 //        } cout << "\v" << endl;
 //    } cout << endl;

	// cout << "previous vertex" << endl;
 //    for (int row = 0 ; row < HEIGHT; row++) {
 //        for (int col = 0; col < WIDTH; col++) {
 //            cout << prev_vertex[(row * WIDTH + col)] << "\t";
 //        } cout << "\v" << endl;
 //    } cout << endl;

	// cout << " distance from source " << endl;
 //    for (int row = 0 ; row < HEIGHT; row++) {
 //        for (int col = 0; col < WIDTH; col++) {
 //            cout << distance_from_source[(row * WIDTH + col)] << "\t";
 //        } cout << "\v" << endl;
 //    } cout << endl;

	cout <<  "in see_stuff: direction to go" << endl;
    for (int row = 0 ; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            cout << "(" << current_floor.tiles[row][col].desired_direction_in_x << "," << current_floor.tiles[row][col].desired_direction_in_y <<")" << "\t";
        } cout << "\v" << endl;
    } cout << endl;
	// cout <<  "testing direction to go" << endl;
 //    for (int row = 0 ; row < HEIGHT; row++) {
 //        for (int col = 0; col < WIDTH; col++) {
 //            cout << "(" << current_floor.get_tile(row,col).desired_direction_in_x << "," << current_floor.get_tile(row,col).desired_direction_in_y <<")" << "\t";
 //        } cout << "\v" << endl;
 //    } cout << endl;
 //    cout << current_floor.get_tile(7,7).desired_direction_in_x << current_floor.get_tile(7,7).desired_direction_in_y << endl;


	// cout << "wall force" << endl;
 //    for (int row = 0 ; row < HEIGHT; row++) {
 //        for (int col = 0; col < WIDTH; col++) {
 //            cout << "(" << current_floor.tiles[row][col].wall_force_in_x << "," << current_floor.tiles[row][col].wall_force_in_y <<")" << "\t";
 //        } cout << "\v" << endl;
 //    } cout << endl;

	// traversal pattern
    // for (int row = 0 ; row < HEIGHT; row++) {
    //     for (int col = 0; col < WIDTH; col++) {
    //         // cout << prev_vertex[row * WIDTH + col] << "\t";
    //         cout << was_processed[row * WIDTH + col] << "\t";
    //     } cout << "\v" << endl;
    // } cout << endl;

}
#endif
