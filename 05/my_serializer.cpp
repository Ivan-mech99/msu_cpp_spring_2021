#include <iostream>
#include <sstream>
#include <cassert>
#include "my_serializer.h"

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
  if (ans) {
    value = stoi(text);
    return Error::NoError;
  } else {
    return Error::NoError;
  }
}

Error Deserializer::inner_load(bool &value) {
  string text;
  in_ >> text;
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
