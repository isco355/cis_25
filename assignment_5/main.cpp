#include <iostream>
#include <string>

using namespace std;
int main() {

  string user_name = {};
  double balance = 0;
  double deposit = 0;
  double withdrawal = 0;
  int option = 0;

  std::cout << "Enter user name account holder:" << std::endl;
  cin >> user_name;

  std::cout << "Enter start balance:" << std::endl;
  cin >> balance;
  if (balance > 0) {
    std::cout << user_name << " Welcome to your account" << std::endl;
    std::cout << "Balance: $" << balance << std::endl;

    std::cout << "1) Make a Deposit" << std::endl;
    std::cout << "2) Make a Withdrawal" << std::endl;
    std::cout << "Enter option" << std::endl;
    cin >> option;
    std::cout << "options :" << option << std::endl;
    switch (option) {
    case 1:
      std::cout << "Enter deposit amount:" << std::endl;
      cin >> deposit;

      if (deposit > 0) {

        std::cout << "deposit amount $: " << deposit << std::endl;
        balance += deposit;
      } else {
        std::cout << "deposit should be greater than zero" << std::endl;
      }
      break;
    case 2:

      std::cout << "Enter withdrawal:" << std::endl;
      cin >> withdrawal;

      if (withdrawal <= balance) {

        std::cout << "withdrawal amount $: " << withdrawal << std::endl;
        balance -= withdrawal;
      } else {
        std::cout << "withdrawal should be greater than zero" << std::endl;
      }
      break;
    default:
      std::cout << "invalid opton" << std::endl;
      break;
    }

  } else {
    std::cout << "balance should be zero or greater" << std::endl;
  }

  std::cout << "current balance: $" << balance << std::endl;

  return 0;
}
