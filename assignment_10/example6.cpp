
#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
  char str[100];
  std::cout << "Enter a string: ";
  cin.get(str, 100);
  std::cout << "You entered: " << str << std::endl;
}
