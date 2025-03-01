#include <iostream>
#include <string>

using namespace std;
int main() {

  string user_name = {};
  double balance = 0;
  double deposit = 0;
  double withdrawal = 0;

  std::cout << "Enter user name account holder:" << std::endl;
  cin >> user_name;

  std::cout << "Enter start balance:" << std::endl;
  cin >> balance;

  std::cout << "Enter deposit amount:" << std::endl;
  cin >> deposit;

  std::cout << "Enter withdrawal:" << std::endl;
  cin >> withdrawal;

  std::cout << "USER NAME: " << user_name << std::endl;
  if (balance > 0) {

    std::cout << "initial balance amount $: " << balance << std::endl;
  } else {
    std::cout << "balance should be zero or greater" << std::endl;
  }

  if (deposit > 0) {

    std::cout << "deposit amount $: " << deposit << std::endl;
  } else {
    std::cout << "deposit should be greater than zero" << std::endl;
  }

  if (withdrawal <= balance) {

    std::cout << "withdrawal amount $: " << withdrawal << std::endl;
  } else {
    std::cout << "withdrawal should be greater than zero" << std::endl;
  }

  return 0;
}
