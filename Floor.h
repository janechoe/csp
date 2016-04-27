/* the class for storing the floor information */
#ifndef Floor_H
#define Floor_H

#include <vector>

using namespace std;

class Floor {
    private:
        int width, height;  /* width and height of the floor*/
        struct Tile{        /* each unit of the floor is modelled as a tile */
            int x, y;       /* co-ordinate of the tile on the floor. code-yellow*/
            char color;     /* color of that specific co-ordinate */
        };
        
        vector<vector<struct Tile*>> tiles_p;   /* store pointer to each tile on the floor */
        

        /* To Do */
        // eventually store a desired direction from the position
        // as it the direction is just the function of where 
        // the agent it.
    public:
        Floor(int w, int h):width{w}, height{h} {
            for(int y = 0; y < height; y++) {
                for(int x = 0; x < width; x++) {
                    char color = (x + y) % 255;
                    Tile current_tile = {x, y, color};
                    tiles_p[y].push_back(&current_tile);
                }
            }
        };
        ~Floor();
};
#endif
