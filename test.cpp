#include <iostream>
#include <vector>
#include "Floor.h"

using namespace std;

int main() {
  int width = 10; int height = 10;
  Floor f;
  f.set_values(width, height);
  f.set_color(0, 0, 100);
  for (int i = 0; i < height; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      cout << f.tiles[i][j].color << "\t";
    }
    cout << endl;
  }
  return 0;
}
