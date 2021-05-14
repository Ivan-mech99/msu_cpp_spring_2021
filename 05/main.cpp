#include <iostream>
#include <sstream>
#include <cassert>
#include "my_serializer.h"

void Default_test() {
  Data x{1, true, 2};
  std::stringstream stream;
  Serializer serializer(stream);
  const Error errs = serializer.save(x);
  assert(errs == Error::NoError);
  string res = "1 true 2 ";
  assert(res == stream.str());
  Data y{0, false, 0};
  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);
  assert(err == Error::NoError);
  assert(x.a == y.a);
  assert(x.b == y.b);
  assert(x.c == y.c);
}

void Only_bool_test() {
  bool3 x{false, true, true};
  std::stringstream stream;
  Serializer serializer(stream);
  const Error errs = serializer.save(x);
  assert(errs == Error::NoError);
  string res = "false true true ";
  assert(res == stream.str());
  Data y{0, false, 0};
  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);
  assert(err == Error::CorruptedArchive);
  assert(0 == y.a);
  assert(false == y.b);
  assert(0 == y.c);
}

void Incorrect_fields_num_test() {
  cout << "Serialize_2_to_3" << endl;
  num_bool x{111, true};
  std::stringstream stream;
  Serializer serializer(stream);
  const Error errs = serializer.save(x);
  assert(errs == Error::NoError);
  string res1 = "111 true ";
  assert(res1 == stream.str());
  Data y{1, true, 2};
  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);
  assert(err == Error::CorruptedArchive);
  assert(y.a == x.a);
  assert(y.b == x.b);
  assert(y.c == 2);
  cout << "Serialize_4_to_3" << endl;
  num_bool_num_num z{1, true, 78, 55};
  std::stringstream stream1;
  Serializer serializer1(stream1);
  const Error errs1 = serializer1.save(z);
  assert(errs1 == Error::NoError);
  string res2 = "1 true 78 55 ";
  assert(res2 == stream1.str());
  Deserializer deserializer1(stream1);
  const Error err2 = deserializer1.load(y);
  assert(y.a == z.a);
  assert(y.b == z.b);
  assert(y.c == z.c);
  assert(err2 == Error::CorruptedArchive);
}

void One_field_structures_test() {
  cout << "One-field bool test!" << endl;
  just_bool x{true};
  std::stringstream stream;
  Serializer serializer(stream);
  const Error errs = serializer.save(x);
  assert(errs == Error::NoError);
  string res1 = "true ";
  assert(res1 == stream.str());
  just_bool y{false};
  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);
  assert(err == Error::NoError);
  assert(x.a == y.a);
  cout << "One-field uint_64t test!" << endl;
  just_num x1{1600};
  std::stringstream stream1;
  Serializer serializer1(stream1);
  const Error errs1 = serializer1.save(x1);
  assert(errs1 == Error::NoError);
  string res2 = "1600 ";
  assert(res2 == stream1.str());
  just_num y1{243};
  Deserializer deserializer1(stream1);
  const Error err1 = deserializer1.load(y1);
  assert(err1 == Error::NoError);
  assert(x1.a == y1.a);
}

void Incorrect_numerical_tokens() {
  cout << "Biggest numerical token test" << endl;
  uint64_t temp_hold = 18446744073709551615UL;
  just_num x1{temp_hold};
  std::stringstream stream1;
  Serializer serializer1(stream1);
  const Error errs = serializer1.save(x1);
  assert(errs == Error::NoError);
  string res1 = "18446744073709551615 ";
  assert(res1 == stream1.str());
  just_num y1{243};
  Deserializer deserializer1(stream1);
  const Error err1 = deserializer1.load(y1);
  assert(err1 == Error::NoError);
  assert(x1.a == y1.a);
  cout << "Token out of limitt" << endl;
  string token0 = "19446744073709551615 ";
  std::stringstream stream2;
  stream2 << token0;
  just_num y2{543};
  Deserializer deserializer2(stream2);
  const Error err2 = deserializer2.load(y2);
  assert(err2 == Error::CorruptedArchive);
  assert(543 == y2.a);
  cout << "Not completely numerical token" << endl;
  std::stringstream stream3;
  string token = "1z446744073709551615 ";
  stream3 << token;
  just_num y3{543};
  Deserializer deserializer3(stream3);
  const Error err3 = deserializer3.load(y3);
  assert(err3 == Error::CorruptedArchive);
  assert(543 == y3.a);
}

void Special_cases_01false_01_test() {
  num_num_bool x{0, 1, false};
  std::stringstream stream;
  Serializer serializer(stream);
  const Error errs = serializer.save(x);
  assert(errs == Error::NoError);
  string res = "0 1 false ";
  assert(res == stream.str());
  bool3 y{false, false, true};
  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);
  assert(err == Error::CorruptedArchive);
  assert(y.a == false);
  assert(y.b == false);
  assert(y.c == true);
  num_num x1{0, 1};
  std::stringstream stream1;
  Serializer serializer1(stream1);
  const Error errs1 = serializer1.save(x1);
  assert(errs1 == Error::NoError);
  string res1 = "0 1 ";
  assert(res1 == stream1.str());
  num_num y1{546, 756};
  Deserializer deserializer1(stream1);
  const Error err1 = deserializer1.load(y1);
  assert(err1 == Error::NoError);
  assert(y1.a == 0);
  assert(y1.b == 1);
}

int main() {
  Default_test();
  Only_bool_test();
  Incorrect_fields_num_test();
  One_field_structures_test();
  Incorrect_numerical_tokens();
  Special_cases_01false_01_test();
  cout << "Success!" << endl;
  return 0;
}

