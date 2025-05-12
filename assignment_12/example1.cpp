#include <iostream>

class MyClass {
public:
  void myMethod() { std::cout << "Hellow world!" << std::endl; };
};

int main() {
  MyClass myObj;
  myObj.myMethod();
}
