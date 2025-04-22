

#include <iostream>
using namespace std;
int main(int argc, char *argv[]) {
  string str;
  std::cout << "Enter a string: ";
  getline(cin, str);
  std::cout << "You entered: " << str << std::endl;
}
