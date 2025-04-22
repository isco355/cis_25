
#include <iostream>
// global variable
int array_length = 1000;

void displayMenuOptions() {
  std::cout << "Enter 1. Output all integer values" << std::endl;
  std::cout << "Enter 2. Output the highest value" << std::endl;
  std::cout << "Enter 3. All Output the lowest value" << std::endl;
  std::cout << "Enter 4. Sum of all values and the mean average" << std::endl;
  std::cout << "Enter 5. Enter a search value" << std::endl;
  std::cout << "Enter 6: Access the middle 2 elements in the array"
            << std::endl;
  std::cout << "Enter 7 or 0: Exit" << std::endl;
}

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
void findMinValue(int *values) {
  int index = 1;
  int min_value = values[0];
  int min_value_index = 0;
  while (index < array_length) {
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
void findMaxValue(int *values) {
  int index = 1;
  int max_value = values[0];
  int max_value_index = 0;
  while (index < array_length) {
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
void mean(int *values) {
  int index = 0;
  float sum = 0;
  while (index < array_length) {
    int current_element = values[index];
    sum += current_element;

    ++index;
  }
  float mean_average = sum / array_length;
  std::cout << "Mean: " << mean_average << std::endl;
}

void visitAllELements(int *random_values) {

  int index = 0;
  while (index < array_length) {
    int element = random_values[index];
    std::cout << element << " ";
    ++index;
  }
  std::cout << std::endl;
}
void findValueOccurrences(int *random_values) {
  int index = 0;
  bool element_found = false;
  int target = 0;
  std::cout << "Enter target value: ";
  std::cin >> target;
  while (index < array_length) {
    int element = random_values[index];
    if (target == element) {
      std::cout << "value:" << element << " Index: " << index << std::endl;
      element_found = true;
    }
    ++index;
  }
  if (element_found == 0) {
    std::cout << " value is not in array" << std::endl;
  }
}
void middleElements(int *random_values) {

  int right_middle_index = array_length / 2;
  int left_middle_index = right_middle_index - 1;
  int left_element = random_values[right_middle_index];
  int right_element = random_values[left_middle_index];
  std::cout << "Elements: " << "( " << left_element << " , " << right_element
            << " )" << std::endl;
  std::cout << "Index: " << "( " << left_middle_index << " , "
            << right_middle_index << " )" << std::endl;
}
void executeOption(int menu_option, int *random_values) {
  switch (menu_option) {
  case 1:
    visitAllELements(random_values);
    break;
  case 2:
    findMaxValue(random_values);
    break;
  case 3:
    findMinValue(random_values);
    break;
  case 4:
    mean(random_values);
    break;
  case 5:
    findValueOccurrences(random_values);
    break;
  case 6:
    middleElements(random_values);
    break;
  default:
    std::cout << "UNKNOW OPTION" << std::endl;
    break;
  }
}

int main(int argc, char *argv[]) {

  int *random_values{new int[array_length]};
  int menu_option = 0;

  generateValues(random_values);
  while (true) {
    displayMenuOptions();
    std::cout << "Enter menu option: ";
    std::cin >> menu_option;

    if (menu_option == 7 or menu_option == 0) {
      break;
    }
    executeOption(menu_option, random_values);
    std::cout << std::endl;
  }
  return 0;
}
