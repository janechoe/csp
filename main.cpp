#include <iostream>
#include <vector>
#include "Floor.h"

using namespace std;


int main() {
    cout << "All gut!" << endl;
    //read the config file and get width and height
    int width = 10, height = 10;
    //instantiate a floor class
    Floor evac_floor = new Floor(width, height);
    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include "Floor.h"

using namespace std;

int initiate_floor(Floor *f) {
    int width, height;
    int color;
    ifstream colorFile;

    //read the values from the file
    colorFile.open("erb1_pixelValues.txt", ios::in);
    colorFile >> width;
    colorFile >> height;
    // Floor f;
    f->set_values(width, height);

    //populate the floor with color values
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            colorFile >> color;
            f->set_color(row,col,color);
        }
    }
    colorFile.close();
    return 0;
}

int main() {
    //initiate the floor
    Floor f;
    initiate_floor(&f);
    return 0;
}