#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> v = {1, 4, 6, 7, 9};

  // Iterating through vector
  for (int i = 0; i < v.size(); i++)
    std::cout << v[i] << " ";
  std::cout << endl;
  return 0;
}
