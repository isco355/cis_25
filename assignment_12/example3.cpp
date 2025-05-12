
#include <iostream>

class Room {
public:
  double length;
  double breadth;
  double height;
  double calculate_area() { return length * breadth; }
  double calculate_volume() { return length * breadth * height; }
};

int main() {
  Room room1;
  room1.length = 42.5;
  room1.breadth = 30.8;
  room1.height = 19.2;
  std::cout << "Area of Room=" << room1.calculate_area() << std::endl;
  std::cout << "Volume of Room=" << room1.calculate_volume() << std::endl;
}
