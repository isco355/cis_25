#include <cstdlib>
#include <iostream>

using namespace std;
int main() {

  string user_name = "";
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

  std::cout << "initial balance amount $: " << balance << std::endl;

  std::cout << "deposit amount $: " << deposit << std::endl;

  std::cout << "withdrawal amount $: " << withdrawal << std::endl;
  balance = (balance + deposit) - withdrawal;
  std::cout << "Final balance:" << balance << std::endl;
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
