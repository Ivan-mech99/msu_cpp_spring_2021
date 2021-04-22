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

  template <class T>
  Error process(T &&value) {
    Error err;
    err = inner_load(value);
    if (err == Error::CorruptedArchive) {
      return Error::CorruptedArchive;
    } else {
      return Error::NoError;
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

#endif
