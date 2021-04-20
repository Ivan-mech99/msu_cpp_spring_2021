#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <cassert>
#include <sstream>
#include "my_parser.h"

using std::vector;
using std::set;
using std::cout;
using std::string;
using std::endl;

void Start_parsing() { cout << "Parsing has started" << endl; }

string Word_transform(string token) {
  token = "[[" + token + "]]";
  return token;
}

string Digit_transform(uint64_t token) {
  string token1;
  token1 = "{{" + std::to_string(token) + "}}";
  return token1;
}

void Write_to_file(const string &parsed) {
  std::ofstream out;
  cout << "Parsing has ended. Writing to file" << endl;
  out.open("Parsed text.txt");
  out << parsed;
  out.close();
}

void Parse_empty_string() {
  TokenParser tp;
  string test = "";
  string ans = "";
  tp.Basic_parser(test);
  assert(tp.result == ans);
}

void Parse_without_callbacks() {
  string test =
      "ab1c\t\n9012  gfkpr data_science\n0+24\t\t  0091 kskxa QWERRTY";
  string ans = "ab1c 9012 gfkpr\ndata_science 0+24 0091\nkskxa QWERRTY ";
  TokenParser tp;
  tp.Basic_parser(test);
  assert(tp.result == ans);
}

void Parse_with_all_callbacks() {
  string test =
      "ab1c\t\n9012  gfkpr data_science\n0+24\t\t  0091 kskxa QWERRTY";
  string ans =
      "[[ab1c]] {{9012}} [[gfkpr]]\n[[data_science]] [[0+24]] "
      "{{91}}\n[[kskxa]] [[QWERRTY]] ";
  TokenParser tp;
  tp.SetStartCallback(Start_parsing);
  tp.SetEndCallback(Write_to_file);
  tp.SetDigitTokenCallback(Digit_transform);
  tp.SetWordTokenCallback(Word_transform);
  tp.Basic_parser(test);
  assert(tp.result == ans);
}

void Parse_only_words() {
  string test =
      "ab1c\t\n9012  gfkpr data_science\n0+24\t\t  0091 kskxa QWERRTY";
  string ans =
      "[[ab1c]] 9012 [[gfkpr]]\n[[data_science]] [[0+24]] 0091\n[[kskxa]] "
      "[[QWERRTY]] ";
  TokenParser tp;
  tp.SetWordTokenCallback(Word_transform);
  tp.Basic_parser(test);
  assert(tp.result == ans);
}

void Parse_only_digits() {
  string test =
      "ab1c\t\n9012  gfkpr data_science\n0+24\t\t  0091 kskxa QWERRTY";
  string ans = "ab1c {{9012}} gfkpr\ndata_science 0+24 {{91}}\nkskxa QWERRTY ";
  TokenParser tp;
  tp.SetDigitTokenCallback(Digit_transform);
  tp.Basic_parser(test);
  assert(tp.result == ans);
}

void Check_last_callback() {
  string test =
      "ab1c\t\n9012  gfkpr data_science\n0+24\t\t  0091 kskxa QWERRTY";
  string ans =
      "[[ab1c]] {{9012}} [[gfkpr]]\n[[data_science]] [[0+24]] "
      "{{91}}\n[[kskxa]] [[QWERRTY]] \n";
  string from_file = "";
  string line;
  TokenParser tp;
  tp.SetStartCallback(Start_parsing);
  tp.SetEndCallback(Write_to_file);
  tp.SetDigitTokenCallback(Digit_transform);
  tp.SetWordTokenCallback(Word_transform);
  tp.Basic_parser(test);
  std::ifstream in;
  in.open("Parsed text.txt");
  while (getline(in, line, '\n')) {
    from_file = from_file + line + '\n';
  }
  assert(ans == from_file);
}

void Parse_special_numbers_with_3_callbacks() {
  string test =
      "18446744073709551615 28446744073709551615 0018446744073709551615 "
      "18436744073709551615 12300087 1844674407370955161556788 1";
  string ans =
      "{{18446744073709551615}} [[28446744073709551615]] "
      "{{18446744073709551615}}\n"
      "{{18436744073709551615}} {{12300087}} "
      "[[1844674407370955161556788]]\n{{1}} ";
  TokenParser tp;
  tp.SetStartCallback(Start_parsing);
  tp.SetDigitTokenCallback(Digit_transform);
  tp.SetWordTokenCallback(Word_transform);
  tp.Basic_parser(test);
  assert(tp.result == ans);
}

void Space_string_test() {
  string test = "                   ";
  string ans = "";
  TokenParser tp;
  tp.SetStartCallback(Start_parsing);
  tp.SetDigitTokenCallback(Digit_transform);
  tp.SetWordTokenCallback(Word_transform);
  tp.Basic_parser(test);
  assert(tp.result == ans);
}

void One_token_string() {
  string test_digit = "1";
  string test_word = "a";
  string ans1 = "{{1}} ";
  string ans2 = "[[a]] ";
  TokenParser tp;
  tp.SetStartCallback(Start_parsing);
  tp.SetDigitTokenCallback(Digit_transform);
  tp.SetWordTokenCallback(Word_transform);
  tp.Basic_parser(test_digit);
  bool res1 = (tp.result == ans1);
  tp.Basic_parser(test_word);
  bool res2 = (tp.result == ans2);
  assert(res1 && res2);
}

int main() {
  Parse_empty_string();
  Parse_without_callbacks();
  Parse_with_all_callbacks();
  Parse_only_words();
  Parse_only_digits();
  Check_last_callback();
  Parse_special_numbers_with_3_callbacks();
  Space_string_test();
  One_token_string();
  cout << "Success! " << endl;
  return 0;
}

