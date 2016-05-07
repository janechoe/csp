/* the class for storing the floor information */
#ifndef Floor_H
#define Floor_H

#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class Floor {
    friend class Graph;
    private:
        int width, height;
        struct Tile{        /* each unit of the floor is modelled as a tile */
            int desired_direction_in_x, desired_direction_in_y;
            int wall_force_in_x = 0, wall_force_in_y = 0;
            int color;     /* color of that specific co-ordinate */
        };
        vector< vector<struct Tile> > tiles; /* Array of tiles on the floor */
    public:
        int set_values(const char *);
        int set_color(int, int, int);
        int get_width();
        int get_height();
        int get_area();
        int set_wall_force(int, int, int, int);
        int process_wall_force(int, int);
        int normalize_wall_force(int, int);
        int set_direction(int, int, int);
        int get_tile_color(int, int);
           
    public:
        Floor()  {};
        ~Floor() {};
};

int Floor::set_values(const char *filename) {
    //read the values from the file
    ifstream colorFile;
    colorFile.open(filename, ios::in);
    colorFile >> width;
    colorFile >> height;
    for (int row = 0; row < height; row++) {
        tiles.push_back(vector<struct Tile> (width) );
        for(int col = 0; col < width; col++) {
            Tile tile;
            colorFile >> tile.color;
            tiles[row][col] = tile; 
        } 
    }
    colorFile.close();
    return 0;
}
int Floor::get_width() {
    return width;
}
int Floor::get_height() {
    return height;
}
int Floor::get_area() {
    return height*width;
}
int Floor::set_color(int row, int col, int c) {
    tiles[row][col].color = c;
}
int Floor::get_tile_color(int row, int col) {
    return tiles[row][col].color;
}
int Floor::set_direction(int vertex, int xdirection, int ydirection) {
    tiles[vertex/width][vertex%width].desired_direction_in_x = xdirection;
    tiles[vertex/width][vertex%width].desired_direction_in_y = ydirection;
    return 0;
}
int Floor::set_wall_force(int row, int col, int xdirection, int ydirection) {
    tiles[row][col].wall_force_in_x += xdirection;
    tiles[row][col].wall_force_in_y += ydirection;
    return 0;
}

int Floor::normalize_wall_force(int row, int col) {
    // float magnitude = pow(pow(tiles[row][col].wall_force_in_x,2) + pow(tiles[row][col].wall_force_in_y,2),0.5);
    float magnitude = pow(pow(2,2) + pow(2,2),0.5);
    tiles[row][col].wall_force_in_x /= magnitude;
    tiles[row][col].wall_force_in_y /= magnitude;
}


#endif
