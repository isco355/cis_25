
#include <iostream>
using namespace std;
bool insideRange(int value, int start, int end) {
  bool in_range = ((value >= start) && (value <= end));
  return in_range;
}
bool isNumericCharacter(char character) {
  bool is_numeric = insideRange(character, 48, 57);
  return is_numeric;
}
bool isAlphabetLetter(char character) {

  bool is_alphabet_letter =
      insideRange(character, 65, 90) || insideRange(character, 97, 122);
  return is_alphabet_letter;
}
bool isSpecialCharacter(char character) {

  bool is_special_character =
      insideRange(character, 33, 47) || insideRange(character, 58, 64) ||
      insideRange(character, 91, 96) || insideRange(character, 123, 126);
  return is_special_character;
}
bool isVowel(char character) {
  bool uppercase_vowel = (character == 65) || (character == 69) ||
                         (character == 73) || (character == 79) ||
                         (character == 85) || (character == 89);
  bool lowercase_vowel = (character == 97) || (character == 101) ||
                         (character == 105) || (character == 111) ||
                         (character == 117) || (character == 121);
  bool is_vowel = uppercase_vowel || lowercase_vowel;
  return is_vowel;
}

int main(int argc, char *argv[]) {
  int vowel_counter = 0;
  int cosonants_counter = 0;
  int numeric_counter = 0;
  int special_counter = 0;
  string user_input;
  std::cout << "Type something: ";
  getline(cin, user_input);

  for (char character : user_input) {
    if (isAlphabetLetter(character)) {
      if (isVowel(character)) {
        vowel_counter++;
      } else {
        cosonants_counter++;
      }
    } else if (isNumericCharacter(character)) {
      numeric_counter++;
    } else if (isSpecialCharacter(character)) {
      special_counter++;
    }
  }

  if (vowel_counter > 0) {
    std::cout << vowel_counter << " Vowels, ";
  }
  if (cosonants_counter > 0) {
    std::cout << cosonants_counter << " consotants, ";
  }
  if (numeric_counter > 0) {
    std::cout << numeric_counter << " numberic values, ";
  }

  if (special_counter > 0) {
    std::cout << special_counter << " special characters, ";
  }
  std::cout << std::endl;
}
