#include <iostream>

int main() {
  int i = 0;
  while (i <= 100) {
    std::cout << i << " - ";
    i += 2;
  };
  std::cout << std::endl;
  return 0;
}
