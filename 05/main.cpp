#include <iostream>
#include <sstream>
#include <cassert>
#include "my_serializer.h"

void Default_test() {
  Data x{1, true, 2};
  std::stringstream stream;
  Serializer serializer(stream);
  serializer.save(x);
  Data y{0, false, 0};
  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);
  assert(err == Error::NoError);
  assert(x.a == y.a);
  assert(x.b == y.b);
  assert(x.c == y.c);
}

void Only_bool_test() {
  Data x{false, true, true};
  std::stringstream stream;
  Serializer serializer(stream);
  serializer.save(x);
  Data y{0, false, 0};
  Deserializer deserializer(stream);
  const Error err = deserializer.load(y);
  assert(err == Error::NoError);
  assert(x.a == y.a);
  assert(x.b == y.b);
  assert(x.c == y.c);
}

int main() {
  Default_test();
  Only_bool_test();
  cout << "Success!" << endl;
  return 0;
}
