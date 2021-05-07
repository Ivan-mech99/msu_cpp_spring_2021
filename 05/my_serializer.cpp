#include <iostream>
#include <sstream>
#include <cassert>
#include "my_serializer.h"

bool check(string num) {
  string max_num = "9223372036854775807";
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
    if (num <= max_num) {
      return true;
    } else {
      return false;
    }
  }
 return true;
}
void Serializer::inner_save(bool &value) {
  string ans1 = "true ";
  string ans2 = "false ";
  if (value == 1) {
    out_ << ans1;
  } else {
    out_ << ans2;
  }
}

void Serializer::inner_save(uint64_t &value) { out_ << value << Separator; }

Error Deserializer::inner_load(uint64_t &value) {
  string text;
  in_ >> text;
  int ans = 1;
  size_t i;
  for (i = 0; i < text.length(); i++) {
    ans = isdigit(text[i]);
    if (ans == 0) {
      break;
    }
  }
  bool res1 = check(text);
  if (res1 == false || ans == 0) {
    cout << "Incorrect numerical token" << endl;
    return Error::CorruptedArchive;
  }
  if (ans) {
    if (text.length() == 0) {
      cout << "CorruptedArchive: not enough args for deserialization" << endl;
      return Error::CorruptedArchive;
    }
    value = stoull(text);
    return Error::NoError;
  } else {
    return Error::CorruptedArchive;
  }
}

Error Deserializer::check_extra_fields() {
  string text;
  in_ >> text;
  if (text.length() != 0) {
    cout << "CorruptedArchive: Too many fields!" << endl;
    return Error::CorruptedArchive;
  } else {
    return Error::NoError;
  }
}
Error Deserializer::inner_load(bool &value) {
  string text;
  in_ >> text;
  if (text.length() == 0) {
    cout << "CorruptedArchive: not enough args for deserialization" << endl;
    return Error::CorruptedArchive;
  }
  string ans1 = "true";
  string ans2 = "false";
  if (text == ans1) {
    value = true;
  } else if (text == ans2) {
    value = false;
  } else {
    return Error::CorruptedArchive;
  }
  return Error::NoError;
}
