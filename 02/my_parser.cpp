#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <sstream>
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

bool TokenParser::IsSpaceTabEnd(char symbol) {
  if (symbol == ' ' || symbol == '\n' || symbol == '\t')
    return true;
  else
    return false;
}

bool TokenParser::Uint_checker(string token) {
  size_t treshold_length = 20;
  string treshold_num = "18446744073709551615";
  size_t i;
  bool flag = false;
  string new_token = "";
  string new_treshold_num = "";
  size_t num_length = token.length();
  for (i = 0; i < token.length(); i++) {
    if (!flag && (token[i] == '0')) {
      num_length--;
    } else if (token[i] != '0') {
      flag = true;
    }
  }
  if (num_length > treshold_length) {
    return false;
  } else if (num_length < treshold_length) {
    return true;
  } else {
    if (token.length() < treshold_length) {
      for (i = 0; i < treshold_length - token.length(); i++) {
        new_token = new_token + "0";
      }
    } else if (token.length() > treshold_length) {
      for (i = 0; i < token.length() - treshold_length; i++) {
        new_treshold_num = new_treshold_num + "0";
      }
    }
    new_token = new_token + token;
    new_treshold_num = new_treshold_num + treshold_num;
    for (i = 0; i < new_token.length(); i++) {
      if ((new_token[i] - '0') > (new_treshold_num[i] - '0')) {
        return false;
      } else if ((new_token[i] - '0') < (new_treshold_num[i] - '0')) {
        return true;
      }
    }
  }
  return true;
}
int TokenParser::IsTokenInteger(string token) {
  set<char> numbers;
  size_t i;
  bool check;
  for (i = 0; i < 10; i++) {
    numbers.insert(to_string(i)[0]);
  }
  for (i = 0; i < token.length(); i++) {
    if (numbers.count(token[i]) == 0) {
      return 0;
    }
  }
  check = Uint_checker(token);
  return check;
}

void TokenParser::Basic_parser(const string &text_par) {
  result = "";
  string parsed_text = "";
  int num_row = 0;
  int indicator;
  size_t i;
  uint64_t digit_token;
  string text = text_par + " ";
  char prev_symbol = ' ';
  string cur_token = "";
  if (StartCallback != nullptr) {
    StartCallback();
  }
  for (i = 0; i < text.length() + 1; i++) {
    if (IsSpaceTabEnd(prev_symbol) && IsSpaceTabEnd(text[i])) {
      prev_symbol = text[i];
    } else if (IsSpaceTabEnd(prev_symbol) && !IsSpaceTabEnd(text[i])) {
      cur_token = cur_token + text[i];
      prev_symbol = text[i];
    } else if (!IsSpaceTabEnd(prev_symbol) && IsSpaceTabEnd(text[i])) {
      indicator = IsTokenInteger(cur_token);
      if ((indicator == 1) && (DigitTokenCallback != nullptr)) {
        std::stringstream ss(cur_token);
        ss >> digit_token;
        cur_token = DigitTokenCallback(digit_token);
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
