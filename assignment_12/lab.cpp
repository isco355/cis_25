
#include <iostream>
#include <string>
using namespace std;

class Bank_Accont {

public:
  double balance = 0;
  double deposit = 0;
  double withdrawal = 0;

  void doWithdrawal(double withdrawal_amount) {
    double new_balance = balance - withdrawal_amount;
    balance = new_balance;
  };

  void doDeposit(double deposit_amount) {
    double new_balance = balance + deposit_amount;
    balance = new_balance;
  };
};

int main() {
  string user_name;
  double init_balance = 0;
  int option = 0;
  int balance_attempts = 3;

  std::cout << "Enter user name: ";
  std::cin >> user_name;
  while (balance_attempts > 0) {
    std::cout << "Enter start balance $: ";
    cin >> init_balance;
    if (init_balance > 0) {

      Bank_Accont bank_account;
      bank_account.balance = init_balance;
      while (true) {
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << user_name << " Welcome to your account" << std::endl;
        std::cout << "CURRENT BALANCE: $" << bank_account.balance << std::endl;
        std::cout << "menu options(Only enter numbers):" << std::endl;
        std::cout << "0 or  single character: quit program" << std::endl;
        std::cout << "1): deposit" << std::endl;
        std::cout << "2): withdrawal" << std::endl;

        std::cout << "Menu option: ";

        int menu_option;
        cin >> menu_option;
        std::cout << std::endl;
        if (menu_option == 0) {
          break;
        }
        switch (menu_option) {
        case 1: {
          double deposit_amount = 0;
          int deposit_attempts = 3;
          while (deposit_attempts > 0) {
            std::cout << "Enter deposit amount: $";
            cin >> deposit_amount;
            if (deposit_amount > 0) {
              std::cout << "deposit amount $: " << deposit_amount << std::endl;
              bank_account.doDeposit(deposit_amount);
              break;
            } else {
              std::cout << "deposit should be greater than zero" << std::endl;
              --deposit_attempts;
            }
          }
          break;
        };
        case 2: {

          std::cout << "withdrawal" << std::endl;
          double withdrawal_amount = 0;
          int withdrawal_attempts = 3;
          while (withdrawal_attempts > 0) {
            std::cout << "Enter withdraw amount: $";
            cin >> withdrawal_amount;
            if (withdrawal_amount > 0 &&
                withdrawal_amount <= bank_account.balance) {
              std::cout << "withdraw amount $: " << withdrawal_amount
                        << std::endl;
              bank_account.doWithdrawal(withdrawal_amount);
              break;
            } else {
              std::cout
                  << "withdrawal should be greater than zero and withdrawal "
                     "should be less than or equal balance"
                  << std::endl;
              --withdrawal_attempts;
            }
          }

          break;
        };
        default:
          std::cout << "unknown menu_option" << std::endl;
        }
      }
      break;
    } else {
      --balance_attempts;
      std::cout << "INVALID BALANCE" << std::endl;
    }
  }

  return 0;
}
