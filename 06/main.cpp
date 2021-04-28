#include <iostream>
#include <cassert>
#include <sstream>
#include "my_format.h"

void Basic_test() {
  auto text = format("{1}+{1} = {0}", 2, "one");
  assert(text == "one+one = 2");
}

void Out_of_context_braces_test() {
  auto text = format("{1}}+{1} = {0}", 2, "one");
  assert(text == "Brace in position 3 is out of context\n");
}

void Is_not_digit_test() {
  auto text = format("{1}+{1x9v} = {0}", 2, "one");
  assert(text == "Symbol: x in position: 6 is not digit\n");
}

void Empty_braces_test() {
  auto text = format("{1}{}+{1} = {0}", 2, "one");
  assert(text == "Empty braces in positions 3, 4\n");
}

void Incorrect_index_test() {
  auto text = format("{1}+{189} = {0}", 2, "one");
  assert(text == "Index 189 is incorrect\n");
}
int main() {
  Basic_test();
  Out_of_context_braces_test();
  Is_not_digit_test();
  Empty_braces_test();
  Incorrect_index_test();
  std::cout << "Success" << endl;
}

