/* the class for storing the floor information */
#ifndef Floor_H
#define Floor_H

#include <vector>
#include <iostream>
using namespace std;

class Floor {
    friend class Graph;
    private:
        int width, height;
        struct Tile{        /* each unit of the floor is modelled as a tile */
            int row, col;   /* co-ordinate of the tile on the floor. code-yellow*/
            int color;     /* color of that specific co-ordinate */
        };
        vector< vector<struct Tile> > tiles; /* Array of tiles on the floor */
    public:
        struct desired_direction{
            char x;
            char y;
        };
        // int set_values(int, int);
        int set_values(const char *);
        int set_color(int, int, int);
        int get_width();
        int get_height();
        int get_area();
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
    for (int i = 0; i < height; i++) {
        tiles.push_back(vector<struct Tile> (width) );
        for(int j = 0; j < width; j++) {
            Tile tile;
            tile.row = i;
            tile.col = j;
            colorFile >> tile.color;
            tiles[i][j] = tile; 
        } 
    }
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
#endif
