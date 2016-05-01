#include <iostream>
#include <fstream>
#include <vector>
#include "Floor.h"
#include "sample.h"

using namespace std;

int main() {
    //initiate the floor
    Floor f;
    f.set_values("sample2.txt");
    Graph g;
    g.set_floor(&f);
    cout << "before the find_route is called" << &f << endl;
    g.find_route();
    cout << "after the find_route is called " << &f << &g << endl;
    return 0;
}