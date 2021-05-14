#include <iostream>
#include <cassert>
#include <sstream>
#include <stdexcept>
#include "my_format.h"

void Basic_test() {
  auto text = format("{1}+{1} = {0}", 2, "one");
  assert(text == "one+one = 2");
}

void Too_much_args() {
  string text;
  try {
    text = format("{1}+{1} = {0}", 2, "one", "sdfc", 23);
  } catch (std::out_of_range &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  assert(text == "Too much args: 4\n");
}

void Out_of_context_braces_test() {
  string text;
  try {
    text = format("{1}}+{1} = {0}", 2, "one");
  } catch (std::logic_error &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  assert(text == "Brace in position 3 is out of context\n");
}

void Is_not_digit_test() {
  string text;
  try {
    text = format("{1}+{1x9v} = {0}", 2, "one");
  } catch (std::invalid_argument &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  assert(text == "Symbol: x in position: 6 is not digit\n");
}

void Empty_braces_test() {
  string text;
  try {
    text = format("{1}{}+{1} = {0}", 2, "one");
  } catch (std::invalid_argument &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  assert(text == "Empty braces in positions 3, 4\n");
}

void Incorrect_index_test() {
  string text;
  try {
    text = format("{1}+{189} = {0}", 2, "one");
  } catch (std::out_of_range &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  assert(text == "Index 189 is incorrect\n");
}

void Empty_string_test() {
  auto text = format("");
  assert(text == "");
}

void String_without_formatting_test() {
  auto text = format("String without args\n");
  assert(text == "String without args\n");
}

void Nwithoutdelimiters_test() {
  auto text = format("{3}{2}{1}{0}", "one", "two", "three", "four");
  cout << text << endl;
  assert(text == "fourthreetwoone");
}

void ManyN_test() {
  auto text = format("{10}{9}{8}{7}{6}{5}{4}{3}{2}{1}{0}", 1, 2, 3, 4, 5, 6, 7,
                     8, 9, 10, 11);
  cout << text << endl;
  assert(text == "1110987654321");
}

void Only_braces_test() {
  string text;
  try {
    text = format("{}", 2);
  } catch (std::invalid_argument &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  assert(text == "Empty braces in positions 0, 1\n");
  try {
    text = format("{}");
  } catch (std::invalid_argument &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  assert(text == "Empty braces in positions 0, 1\n");
}

void No_num_in_braces_test() {
  string text;
  try {
    text = format("{1}+{1}{} = {0}", 2, "one");
  } catch (std::invalid_argument &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  assert(text == "Empty braces in positions 7, 8\n");
}

void String_in_braces_test() {
  string text;
  try {
    text = format("{{1}+ceta{1} = {0}}", 2, "one");
  } catch (Is_not_digit &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  assert(text == "Symbol: { in position: 1 is not digit\n");
}

void Not_enough_args_test() {
  string text;
  try {
    text = format("{1}+{1} = {0}", 2);
  } catch (std::out_of_range &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  try {
    text = format("{1}+{1} = {0}");
  } catch (std::out_of_range &e) {
    cout << e.what() << endl;
    text = e.what();
  }
}

void Extra_braces_test() {
  string text;
  try {
    text = format("{0}{", 2);
  } catch (std::logic_error &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  assert(text == "Brace in position 3 is out of context\n");
  try {
    text = format("{0}}", 2);
  } catch (std::logic_error &e) {
    cout << e.what() << endl;
    text = e.what();
  }
  assert(text == "Brace in position 3 is out of context\n");
}

int main() {
  Basic_test();
  Too_much_args();
  Out_of_context_braces_test();
  Is_not_digit_test();
  Empty_braces_test();
  Incorrect_index_test();
  Empty_string_test();
  String_without_formatting_test();
  No_num_in_braces_test();
  Nwithoutdelimiters_test();
  ManyN_test();
  Only_braces_test();
  String_in_braces_test();
  Not_enough_args_test();
  Extra_braces_test();
  cout << "Success" << endl;
}

