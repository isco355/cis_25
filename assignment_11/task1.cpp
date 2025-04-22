#include <fstream>
#include <iostream>

int array_length = 1000;
void generateValues(int *random_values) {
  int random_end_range = 1000;
  int i = 0;
  srand(time(0));

  while (i < array_length) {
    int random_value = rand() % random_end_range + 1;
    random_values[i] = random_value;
    ++i;
  }
}
int main(int argc, char *argv[]) {
  int random_values[array_length];
  int menu_option = 0;
  generateValues(random_values);

  std::ofstream myfile("random.txt");
  int i = 0;
  if (myfile.is_open()) {
    while (i < array_length) {
      int element = random_values[i];
      std::cout << element << " ";
      myfile << element << "\n";
      i++;
    }
  }
  myfile.close();
  std::cout << std::endl;

  return 0;
}
