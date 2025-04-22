#include <iostream>
void findValue(int (&values)[5], int target) {
  int index = 0;
  for (int element : values) {
    if (target == element) {
      std::cout << "Element:" << element << " Index: " << index << std::endl;
      return;
    }
    ++index;
  }
  std::cout << "element not found" << std::endl;
}
void findValueOccurrences(int (&values)[5], int target) {
  int index = 0;
  bool element_found = false;
  for (int element : values) {
    if (target == element) {
      std::cout << "Element:" << element << " Index: " << index << std::endl;
      element_found = true;
    }
    ++index;
  }
  if (element_found == 0) {
    std::cout << "element not found" << std::endl;
  }
}
int main(int argc, char *argv[]) {

  int values[5] = {
      1, 2, 3, 4, 1,
  };
  std::cout << "single ocurrence: " << std::endl;
  findValue(values, 2);
  std::cout << std::endl;
  std::cout << "multiple ocurrences : " << std::endl;
  findValueOccurrences(values, 1);

  return 0;
}
