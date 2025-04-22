
#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {

  int num;
  int sum = 0;

  std::cout << "Enter a positve Number" << std::endl;
  std::cin >> num;
  int values[num];
  for (int i = 1; i <= num; ++i) {
    values[i - 1] = i;
    sum += i;
  };
  std::cout << "Total sum: " << sum << std::endl;
  for (int val : values) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
  return 0;
}
