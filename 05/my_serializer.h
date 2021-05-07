#ifndef H_MY_SERIALIZER
#define H_MY_SERIALIZER
#pragma once
#include <iostream>
#include <string>
using std::string;
using std::ostream;
using std::istream;
using std::forward;
using std::cout;
using std::endl;

enum class Error { NoError, CorruptedArchive };

class Serializer {
  ostream &out_;
  static constexpr char Separator = ' ';

 public:
  explicit Serializer(ostream &out) : out_(out) {}

  template <class T>
  Error save(T &object) {
    return object.serialize(*this);
  }

  template <class... ArgsT>

  Error operator()(ArgsT... args) {
    return process(args...);
  }

 private:
  template <class T, class... ArgsT>
  Error process(T &&value, ArgsT &&... args) {
    inner_save(value);
    return process(args...);
  }

  template <class T>
  Error process(T &&value) {
    inner_save(value);
    return Error::NoError;
  }

  void inner_save(bool &value);
  void inner_save(uint64_t &value);
};

class Deserializer {
  istream &in_;

 public:
  explicit Deserializer(istream &in) : in_(in) {}

  template <class T>
  Error load(T &object) {
    return object.serialize(*this);
  }

  template <class... ArgsT>
  Error operator()(ArgsT &&... args) {
    return process(args...);
  }

 private:
  template <class T, class... ArgsT>
  Error process(T &&value, ArgsT &&... args) {
    Error err;
    err = inner_load(value);
    if (err == Error::CorruptedArchive) {
      return Error::CorruptedArchive;
    } else {
      return process(args...);
    }
  }

  Error check_extra_fields();

  template <class T>
  Error process(T &&value) {
    Error err;
    err = inner_load(value);
    if (err == Error::CorruptedArchive) {
      return Error::CorruptedArchive;
    } else {
      return check_extra_fields();
    }
  }

  Error inner_load(bool &value);
  Error inner_load(uint64_t &value);
};

struct Data {
  uint64_t a;
  bool b;
  uint64_t c;

  template <class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(a, b, c);
  }
};

struct num_bool {
  uint64_t a;
  bool b;

  template <class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(a, b);
  }
};

struct bool_num {
  bool a;
  uint64_t b;
  template <class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(a, b);
  }
};

struct num_bool_num_num {
  uint64_t a;
  bool b;
  uint64_t c;
  uint64_t d;
  template <class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(a, b, c, d);
  }
};

struct just_bool {
  bool a;
  template <class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(a);
  }
};

struct just_num {
  uint64_t a;
  template <class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(a);
  }
};

struct bool3 {
  bool a;
  bool b;
  bool c;
  template <class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(a, b, c);
  }
};

struct num_num {
  uint64_t a;
  uint64_t b;
  template <class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(a, b);
  }
};

struct num_num_bool {
  uint64_t a;
  uint64_t b;
  bool c;
  template <class Serializer>
  Error serialize(Serializer &serializer) {
    return serializer(a, b, c);
  }
};

#endif


