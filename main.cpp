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
