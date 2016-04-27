/* the class for storing the floor information */
#ifndef Floor_H
#define Floor_H

#include <vector>

using namespace std;

class Floor {
    //eventually protected
    public:
        int width, height;  /* width and height of the floor*/
        struct Tile{        /* each unit of the floor is modelled as a tile */
            int row, col;       /* co-ordinate of the tile on the floor. code-yellow*/
            char color;     /* color of that specific co-ordinate */
        };

        /* store pointer to each tile on the floor */
        vector< vector<struct Tile*> > tiles_p;   

        /* To Do */
        // eventually store a desired direction from the position
        // as it the direction is just the function of where 
        // the agent it.
    public:
        Floor(int w, int h) : width{w}, height{h} {
            for(int row = 0; row < height; row++) {
                for(int col = 0; col < width; row++) {
                    char color = (row + col) % 255;
                    Tile current_tile = {row, col, color};
                    tiles_p[row][col] = &current_tile;
                }
            }
        };
        ~Floor();
};
#endif
