#include <iostream>
#include <vector>

using namespace std;

int main() {
  int width = 10; int height = 10;
  vector<vector<int>> a(10, vector<int>(10));
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      a[i][j]= i + j;
      // cout << a[i][j] << endl;
    }
  }
  cout << a[1][8] << endl;
  return 0;
}
