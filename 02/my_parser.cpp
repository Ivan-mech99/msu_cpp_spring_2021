#include <string>
#include <vector>
#include <iostream>
#include <set>
#include "my_parser.h"

using std::string;
using std::cout;
using std::vector;
using std::set;
using std::to_string;

TokenParser::TokenParser() {
  StartCallback = nullptr;
  DigitTokenCallback = nullptr;
  WordTokenCallback = nullptr;
  EndCallback = nullptr;
  result = "";
}

int TokenParser::IsSpaceTabEnd(char symbol) {
  if (symbol == ' ' || symbol == '\n' || symbol == '\t')
    return 1;
  else
    return 0;
}

int TokenParser::IsTokenInteger(string token) {
  set<char> numbers;
  int i;
  for (i = 0; i < 10; i++) {
    numbers.insert(to_string(i)[0]);
  }
  for (i = 0; i < int(token.length()); i++) {
    if (numbers.count(token[i]) == 0) {
      return 0;
    }
  }
  return 1;
}

void TokenParser::Basic_parser(const string text_par) {
  result = "";
  string parsed_text = "";
  int num_row = 0;
  int indicator;
  int i;
  string text = text_par + " ";
  char prev_symbol = ' ';
  string cur_token = "";
  if (StartCallback != nullptr) {
    StartCallback();
  }
  for (i = 0; i < int(text.length()) + 1; i++) {
    if (IsSpaceTabEnd(prev_symbol) && IsSpaceTabEnd(text[i])) {
      prev_symbol = text[i];
    } else if (IsSpaceTabEnd(prev_symbol) && !IsSpaceTabEnd(text[i])) {
      cur_token = cur_token + text[i];
      prev_symbol = text[i];
    } else if (!IsSpaceTabEnd(prev_symbol) && IsSpaceTabEnd(text[i])) {
      indicator = IsTokenInteger(cur_token);
      if ((indicator == 1) && (DigitTokenCallback != nullptr)) {
        cur_token = DigitTokenCallback(cur_token);
      } else if ((indicator == 0) && WordTokenCallback != nullptr) {
        cur_token = WordTokenCallback(cur_token);
      }
      if (num_row < 2) {
        parsed_text = parsed_text + cur_token + ' ';
        num_row++;
      } else {
        num_row = 0;
        parsed_text = parsed_text + cur_token + '\n';
      }
      cur_token = "";
      prev_symbol = text[i];
    } else if (!IsSpaceTabEnd(prev_symbol) && !IsSpaceTabEnd(text[i])) {
      cur_token = cur_token + text[i];
      prev_symbol = text[i];
    }
  }
  result = parsed_text;
  if (EndCallback != nullptr) {
    EndCallback(result);
  }
}
