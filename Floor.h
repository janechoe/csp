/* the class for storing the floor information */
#ifndef Floor_H
#define Floor_H

#include <vector>
#include <iostream>
using namespace std;

class Floor {
    //eventually protected
    private:
        int width, height;

    public:
        struct Tile{        /* each unit of the floor is modelled as a tile */
            int row, col;   /* co-ordinate of the tile on the floor. code-yellow*/
            int color;     /* color of that specific co-ordinate */
        };
        struct desired_direction{
            char x;
            char y;
        };
        int set_values(int, int);
        int set_color(int, int, int);
        int get_width();
        int get_height();
        /* store pointer to each tile on the floor */
        vector< vector<struct Tile> > tiles;   

        /* To Do */
        // eventually store a desired direction from the position
        // as it the direction is just the function of where 
        // the agent it.
    public:
        Floor() {
            cout << "floor object being created" << endl;
        };
        ~Floor() {
            cout << "floor object is being destroyed" << endl;
        };
};

int Floor::set_values(int w, int h) {
    width = w;
    height = h;
    for (int i = 0; i < h; i++) {
        tiles.push_back(vector<struct Tile> (w) );
        for(int j = 0; j < w; j++) {
            Tile tile;
            // cout << tile << "\t";
            tile.row = i;
            tile.col = j;
            tile.color = (i+j) % 9;
            tiles[i][j] = tile; 
            // cout << tile.row << tile.col << tile.color << "\t";
        }
        // cout << endl;
    }
}
int Floor::get_width() {
    return width;
}
int Floor::get_height() {
    return height;
}
int Floor::set_color(int row, int col, int c) {
    tiles[row][col].color = c;
}
#endif
