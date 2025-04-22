#include <iostream>
void f(int *x) { *x = *x - 1; }
int main(int argc, char *argv[]) {
  int a = 5;
  std::cout << a << std::endl;
  f(&a);
  std::cout << a << std::endl;
}
