#include <iostream>
#include <string>
using namespace std;

double depositOperation(double current_balance, double deposit) {
  double new_balance = current_balance + deposit;
  return new_balance;
}
double withdrawalOperation(double current_balance, double deposit) {
  double new_balance = current_balance - deposit;
  return new_balance;
}

int main() {

  string user_name = {};
  double balance = 0;
  int option = 0;
  int initial_balance_attemps = 3;

  std::cout << "Enter user name: ";
  std::cin >> user_name;

  while (initial_balance_attemps > 0) {
    std::cout << "Enter start balance $: ";
    cin >> balance;
    if (balance > 0) {
      while (true) {
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << user_name << " Welcome to your account" << std::endl;
        std::cout << "CURRENT BALANCE: $" << balance << std::endl;
        std::cout << "menu options:" << std::endl;
        std::cout << "0): quit menu" << std::endl;
        std::cout << "1): deposit" << std::endl;
        std::cout << "2): withdrawal" << std::endl;

        int menu_option;
        std::cout << "option: ";
        cin >> menu_option;

        if (menu_option == 0) {
          break;
        } else {
          switch (menu_option) {
          case 1: {
            double deposit = 0;
            int attempts = 3;
            while (attempts > 0) {
              std::cout << "Enter deposit amount: $";
              cin >> deposit;
              if (deposit > 0) {
                std::cout << "deposit amount $: " << deposit << std::endl;
                balance = depositOperation(balance, deposit);
                break;
              } else {
                std::cout << "deposit should be greater than zero" << std::endl;
                --attempts;
              }
            }
            break;
          };
          case 2: {

            std::cout << "withdrawal" << std::endl;
            double withdrawal = 0;
            int attempts = 3;
            while (attempts > 0) {
              std::cout << "Enter withdraw amount: $";
              cin >> withdrawal;
              if (withdrawal > 0 && withdrawal <= balance) {
                std::cout << "withdraw amount $: " << withdrawal << std::endl;
                balance = withdrawalOperation(balance, withdrawal);
                break;
              } else {
                std::cout
                    << "withdrawal should be greater than zero and withdrawal "
                       "should be less than or equal balance"
                    << std::endl;
                --attempts;
              }
            }

            break;
          };
          default:
            std::cout << "unknown menu_option" << std::endl;
          }
        }
      }
      break;
    } else {
      --initial_balance_attemps;
      std::cout << "INVALID BALANCE" << std::endl;
    }
  }

  return 0;
}
