#include <iostream>

void displayMonth(int month_number) {

  switch (month_number) {
  case 1:
    std::cout << "31 days in January" << std::endl;
    break;
  case 2:
    std::cout << "28 days in February" << std::endl;
    break;
  case 3:
    std::cout << "31 days in March" << std::endl;
    break;
  case 4:
    std::cout << "30 days in April" << std::endl;
    break;
  case 5:
    std::cout << "30 days in May" << std::endl;
    break;
  case 6:
    std::cout << "30 days in June" << std::endl;
    break;
  case 7:
    std::cout << "31 days in July" << std::endl;
    break;
  case 8:
    std::cout << "29 days in August" << std::endl;
    break;
  case 9:
    std::cout << "30 days in September" << std::endl;
    break;
  case 10:
    std::cout << "31 days in October" << std::endl;
    break;
  case 11:
    std::cout << "28 days in November" << std::endl;
    break;
  case 12:
    std::cout << "31 days in December" << std::endl;
    break;
  default:
    std::cout << "Invalid Month" << std::endl;
  }
}
int main() {
  while (true) {
    int month_number;
    std::cout << "Enter 0 to exit program" << std::endl;
    std::cout << "Enter a month number(1-12): ";
    std::cin >> month_number;
    if (month_number == 0) {
      break;
    } else {
      displayMonth(month_number);
    }
  }

  return 0;
}
