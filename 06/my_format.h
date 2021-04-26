#ifndef H_MY_FORMAT
#define H_MY_FORMAT
#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <ostream>
#include <string>
using std::stringstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::to_string;

class Out_of_context_braces {
 public:
  string what = "";
  Out_of_context_braces(int i) {
    what = "Brace in position " + to_string(i) + " is out of context\n";
  }
};

class Is_not_digit {
 public:
  string what = "";
  Is_not_digit(string symbol, int i) {
    string symb = "" + symbol;
    what =
        "Symbol: " + symb + " in position: " + to_string(i) + " is not digit\n";
  }
};

class Empty_braces {
 public:
  string what = "";
  Empty_braces(int i, int j) {
    what = "Empty braces in positions " + to_string(i) + ", " + to_string(j) +
           "\n";
  }
};

class Incorrect_index {
 public:
  string what = "";
  Incorrect_index(int i) { what = "Index " + to_string(i) + " is incorrect\n"; }
};

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

template <class... ArgsT>
string format(string sentence, ArgsT &&... args) {
  try {
    vector<string> args_vec;
    process(args_vec, args...);
    stringstream formatted;
    int i;
    int situation = 0;
    string cur_token = "";
    for (i = 0; i < int(sentence.length()); i++) {
      if (i == int(sentence.length()) - 1 && sentence[i] == '{') {
        throw Out_of_context_braces(i);
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
      } else if (sentence[i] == '}' && situation == 1 &&
                 sentence[i - 1] != '{' && i > 0) {
        situation = 0;
        int hold = stoi(cur_token);
        if (hold < 0 || hold >= int(args_vec.size())) {
          throw Incorrect_index(hold);
        }
        formatted << args_vec[stoi(cur_token)];
        continue;
      } else if (sentence[i] == '}' && situation == 1 &&
                 sentence[i - 1] == '{' && i > 0) {
        throw Empty_braces(i - 1, i);
      } else if (sentence[i] == '}' && situation == 0) {
        throw Out_of_context_braces(i);
      } else if (sentence[i] != '}' && situation == 1 &&
                 i == (int(sentence.length()) - 1)) {
        throw Out_of_context_braces(i);
      } else if (situation == 1 && (!isdigit(sentence[i]))) {
        string temp = "";
        temp.push_back(sentence[i]);
        throw Is_not_digit(temp, i);
      }
    }
    cout << formatted.str() << endl;
    return formatted.str();
  } catch (Out_of_context_braces e) {
    cout << e.what << endl;
    return e.what;
  } catch (Is_not_digit e) {
    cout << e.what << endl;
    return e.what;
  } catch (Empty_braces e) {
    cout << e.what << endl;
    return e.what;
  } catch (Incorrect_index e) {
    cout << e.what << endl;
    return e.what;
  }
}

#endif
