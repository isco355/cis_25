#include <_stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(int argc, char *argv[]) {
  int total_elements = 1000;
  int random_elements[total_elements];
  int total_sum = 0;
  int i = 0;

  srand(time(0));
  while (i < total_elements) {
    int random_value = rand() % 1000 + 1;
    random_elements[i] = random_value;
    ++i;
  }
  for (int element : random_elements) {
    std::cout << element << " ";
    total_sum += element;
  }

  std::cout << std::endl;
  int length = sizeof(random_elements) / sizeof(random_elements[0]);
  std::cout << "array size: " << length << std::endl;
  std::cout << "total sum of random values: " << total_sum << std::endl;
  return 0;
}
