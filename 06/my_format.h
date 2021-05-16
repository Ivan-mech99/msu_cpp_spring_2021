#ifndef H_MY_FORMAT
#define H_MY_FORMAT
#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <ostream>
#include <string>
#include <stdexcept>
#include <set>
using std::stringstream;
using std::vector;
using std::string;
using std::set;
using std::cout;
using std::endl;
using std::to_string;

class Out_of_context_braces : public std::logic_error {
  std::string err;

 public:
  explicit Out_of_context_braces(const std::string &err_mes)
      : std::logic_error(err_mes), err(err_mes) {}

  const char *what() const noexcept override { return err.c_str(); }
};

class Is_not_digit : public std::invalid_argument {
  std::string err;

 public:
  explicit Is_not_digit(const std::string &err_mes)
      : std::invalid_argument(err_mes), err(err_mes) {}

  const char *what() const noexcept override { return err.c_str(); }
};

class Empty_braces : public std::invalid_argument {
  std::string err;

 public:
  explicit Empty_braces(const std::string &err_mes)
      : std::invalid_argument(err_mes), err(err_mes) {}

  const char *what() const noexcept override { return err.c_str(); }
};

class Incorrect_index : public std::out_of_range {
  std::string err;

 public:
  explicit Incorrect_index(const std::string &err_mes)
      : std::out_of_range(err_mes), err(err_mes) {}

  const char *what() const noexcept override { return err.c_str(); }
};

class much_args : public std::out_of_range {
  std::string err;

 public:
  explicit much_args(const std::string &err_mes)
      : std::out_of_range(err_mes), err(err_mes) {}

  const char *what() const noexcept override { return err.c_str(); }
};

class too_big : public std::overflow_error {
  std::string err;

 public:
  explicit too_big(const std::string &err_mes)
      : std::overflow_error(err_mes), err(err_mes) {}

  const char *what() const noexcept override { return err.c_str(); }
};

template <class T>
void process(T &&token) {
  if (token.size() == 0) cout << "No args" << endl;
}

template <class T>
void process(vector<string> &args_vec, T &&token) {
  stringstream token_read;
  token_read << token;
  args_vec.push_back(token_read.str());
}

template <class T, class... ArgsT>
void process(vector<string> &args_vec, T &&token, ArgsT &&... args) {
  stringstream token_read;
  token_read << token;
  args_vec.push_back(token_read.str());
  process(args_vec, args...);
}

bool check(string num) {
  string max_num = "18446744073709551615";
  if (num.length() > max_num.length()) {
    return false;
  }
  size_t i;
  for (i = 0; i < num.length(); i++) {
    if (isdigit(num[i]) == 0) {
      return false;
    }
  }
  if (num.length() < max_num.length()) {
    return true;
  }
  if (num.length() == max_num.length()) {
    if (num < max_num) {
      return true;
    } else {
      return false;
    }
  }
  return true;
}

template <class... ArgsT>
string format(string sentence, ArgsT &&... args) {
  vector<string> args_vec;
  set<string> used_args;
  process(args_vec, args...);
  stringstream formatted;
  int i;
  string err_mes;
  int situation = 0;
  string cur_token = "";
  for (i = 0; i < int(sentence.length()); i++) {
    if (i == int(sentence.length()) - 1 && sentence[i] == '{') {
      err_mes = "Brace in position " + to_string(i) + " is out of context\n";
      throw Out_of_context_braces(err_mes);
    } else if (sentence[i] != '{' && sentence[i] != '}' && situation == 0) {
      formatted << sentence[i];
      continue;
    } else if (sentence[i] == '{' && situation == 0) {
      situation = 1;
      cur_token = "";
      continue;
    } else if (sentence[i] != '{' && sentence[i] != '}' && situation == 1 &&
               isdigit(sentence[i]) && i != (int(sentence.length()) - 1)) {
      cur_token = cur_token + sentence[i];
      continue;
    } else if (sentence[i] == '}' && situation == 1 && sentence[i - 1] != '{' &&
               i > 0) {
      situation = 0;
      if (!check(cur_token)) {
        err_mes = "Overflow occurs with token " + cur_token + "\n";
        throw too_big(err_mes);
      }
      uint64_t hold = stoull(cur_token);
      if (hold < 0 || hold >= (args_vec.size())) {
        err_mes = "Index " + to_string(hold) + " is incorrect\n";
        throw Incorrect_index(err_mes);
      }
      if (used_args.count(cur_token) == 0) {
        used_args.insert(cur_token);
      }
      formatted << args_vec[stoull(cur_token)];
      continue;
    } else if (sentence[i] == '}' && situation == 1 && sentence[i - 1] == '{' &&
               i > 0) {
      err_mes = "Empty braces in positions " + to_string(i - 1) + ", " +
                to_string(i) + "\n";
      throw Empty_braces(err_mes);
    } else if (sentence[i] == '}' && situation == 0) {
      err_mes = "Brace in position " + to_string(i) + " is out of context\n";
      throw Out_of_context_braces(err_mes);
    } else if (sentence[i] != '}' && situation == 1 &&
               i == (int(sentence.length()) - 1)) {
      err_mes = "Brace in position " + to_string(i) + " is out of context\n";
      throw Out_of_context_braces(err_mes);
    } else if (situation == 1 && (!isdigit(sentence[i]))) {
      string temp = "";
      temp.push_back(sentence[i]);
      err_mes = "Symbol: " + temp + " in position: " + to_string(i) +
                " is not digit\n";
      throw Is_not_digit(err_mes);
    }
  }
  if (used_args.size() < args_vec.size()) {
    err_mes = "Too much args: " + to_string(args_vec.size()) + '\n';
    throw much_args(err_mes);
  }
  cout << formatted.str() << endl;
  return formatted.str();
}

#endif
