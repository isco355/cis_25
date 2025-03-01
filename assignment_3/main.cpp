#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

using namespace std;
void stopFor(int mili_second) {
  this_thread::sleep_for(std::chrono::milliseconds(mili_second));
}
void clearScreen() { std::cout << "\033[2J\033[1;1H"; }
void quitMessage() {
  std::cout << "Enter \"q\" or \"quit\" to exit program" << std::endl;
}
void displayTransactionOptions() {
  std::cout << "Enter \"d\" or \"deposit\" for deposit money in account"
            << std::endl;
  std::cout << "Enter \"w\" or \"widthdraw\" for widthdraw money in account"
            << std::endl;
  std::cout << "Enter transaction type:" << std::endl;
}

bool isOnlyDigits(string text) {
  for (char character : text) {
    bool val = isdigit(character);
    if (val == false) {
      return false;
    }
  }
  return true;
}

bool isQuitCommand(string command) {
  bool condition = command == "q" || command == "quit";
  return condition;
}

int requestValue() {
  clearScreen();
  quitMessage();
  while (true) {
    std::cout << "enter value: " << std::endl;
    string command = "";
    cin >> command;
    if (isQuitCommand(command)) {
      return 0;
    }
    bool is_only_digits = isOnlyDigits(command);
    if (is_only_digits) {
      return stoi(command);
    } else {
      clearScreen();
      std::cout << "value should be only integer " << std::endl;
      stopFor(1000);
    }
  }
}

int processTransaction(string command, int balance) {

  if (command == "d" || command == "deposit") {
    balance += requestValue();
  } else if (command == "w" || command == "widthdraw") {
    balance -= requestValue();
  } else {
    cout << "command not found " << command << std::endl;
    stopFor(1000);
  }
  return balance;
}

int main(int argc, char *argv[]) {

  string transaction_command = "";
  string user_name = "Francisco";
  int balance = 0;

  while (true) {

    clearScreen();
    quitMessage();
    std::cout << "User Name: " << user_name << std::endl;
    std::cout << "Current Balance: $" << balance << std::endl;

    displayTransactionOptions();
    cin >> transaction_command;
    if (isQuitCommand(transaction_command) == true) {
      break;
    }
    balance = processTransaction(transaction_command, balance);
  }

  return 0;
}

// #include <iostream>
// using namespace std;
//
// int main(int argc, char *argv[]) {
//
//   //// basic setup
//   cout << "short int :" << sizeof(short int) << " bytes" << endl;
//   cout << "unsigned short int:" << sizeof(unsigned short int) << " bytes"
//        << endl;
//   cout << "unsigned int:" << sizeof(unsigned int) << " bytes" << endl;
//   cout << "int:" << sizeof(int) << " bytes" << endl;
//   cout << "long int:" << sizeof(long int) << " bytes" << endl;
//   cout << "unsigned long int:" << sizeof(unsigned long int) << " bytes" <<
//   endl; cout << "long long int:" << sizeof(long long int) << " bytes" <<
//   endl; cout << "unsigned long int:" << sizeof(unsigned long long int) << "
//   bytes"
//        << endl;
//   cout << "signed char:" << sizeof(signed char) << " bytes" << endl;
//   cout << "unsigned char:" << sizeof(unsigned char) << " bytes" << endl;
//   cout << "float:" << sizeof(float) << " bytes" << endl;
//   cout << "double:" << sizeof(double) << " bytes" << endl;
//   cout << "long double:" << sizeof(long double) << " bytes" << endl;
//   cout << "wchat_t:" << sizeof(wchar_t) << " bytes" << endl;
//
//   return 0;
// }
