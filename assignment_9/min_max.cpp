
#include <iostream>
void findMinValue(int (&values)[5]) {
  int length = sizeof(values) / sizeof(values[0]);
  int index = 1;
  int min_value = values[0];
  int min_value_index = 0;
  while (index < length) {
    int current_element = values[index];
    if (current_element < min_value) {
      min_value = current_element;
      min_value_index = index;
    }

    ++index;
  }
  std::cout << "mininum value: " << min_value << " index: " << min_value_index
            << std::endl;
}
void findMaxValue(int (&values)[5]) {
  int length = sizeof(values) / sizeof(values[0]);
  int index = 1;
  int max_value = values[0];
  int max_value_index = 0;
  while (index < length) {
    int current_element = values[index];
    if (current_element > max_value) {
      max_value = current_element;
      max_value_index = index;
    }

    ++index;
  }
  std::cout << "Maximum value: " << max_value << " index: " << max_value_index
            << std::endl;
}

void mean(int (&values)[5]) {
  int length = sizeof(values) / sizeof(values[0]);
  int index = 0;
  float sum = 0;
  while (index < length) {
    int current_element = values[index];
    sum += current_element;

    ++index;
  }
  float mean_average = sum / length;
  std::cout << "Mean: " << mean_average << std::endl;
}

int main(int argc, char *argv[]) {

  int values[5] = {
      5, 3, 3, 2, 1,
  };

  std::cout << "Mininum value: " << std::endl;
  findMinValue(values);

  std::cout << std::endl;

  std::cout << "Maximum value: " << std::endl;
  findMaxValue(values);

  std::cout << std::endl;
  mean(values);
  return 0;
}
