
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  std::ifstream file("random.txt");
  std::string line;

  while (std::getline(file, line)) {
    std::cout << line << " ";
  }
  std::cout << std::endl;
  file.close();
  return 0;
}
