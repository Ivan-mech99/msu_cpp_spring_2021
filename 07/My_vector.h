#ifndef H_MY_VECTOR
#define H_MY_VECTOR
#pragma once
#include <iostream>
#include <iterator>

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
  T* cur_pos;

 public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  explicit Iterator(T* pos) : cur_pos(pos) {}

  bool operator==(const Iterator<T>& iter2) const {
    return cur_pos == iter2.cur_pos;
  }

  bool operator!=(const Iterator<T>& iter2) const {
    return !(cur_pos == iter2.cur_pos);
  }

  reference operator*() const { return *cur_pos; }

  Iterator& operator++() {
    ++cur_pos;
    return *this;
  }

  Iterator& operator--() {
    --cur_pos;
    return *this;
  }
};

template <class T>
class Allocator {
 public:
  using value_type = T;
  using pointer = T*;
  using size_type = size_t;

  template <class... ArgsT>
  void construct(pointer pointer1, ArgsT&&... args) {
    new (pointer1) T(args...);
  }

  pointer allocate(size_type mem_amount) { return new T[mem_amount]; }

  void deallocate(pointer ptr) { delete[] ptr; }
};

template <class T>
class My_vector {
  Allocator<T> alloc;
  T* data_vec;
  size_t size_vec;
  size_t size_mem;

 public:
  using iterator = Iterator<T>;
  using reverse_iterator = std::reverse_iterator<Iterator<T>>;

  My_vector(size_t mem_wanted = 8) {
    size_vec = 0;
    size_mem = mem_wanted;
    data_vec = alloc.allocate(size_mem);
  }

  My_vector(T val, size_t mem_wanted = 8) {
    size_t i;
    size_vec = 0;
    size_mem = mem_wanted;
    data_vec = alloc.allocate(size_mem);
    for (i = 0; i < size_mem; i++) {
      size_vec++;
      data_vec[i] = val;
    }
  }

  size_t size() const noexcept { return size_vec; }

  size_t capacity() const noexcept { return size_mem; }

  bool empty() const noexcept {
    if (size_vec == 0) {
      return true;
    } else {
      return false;
    }
  }

  void clear() noexcept { size_vec = 0; }

  T& operator[](size_t index) { return data_vec[index]; }

  Iterator<T> begin() { return Iterator<T>(data_vec); }

  Iterator<T> end() { return Iterator<T>(data_vec + size_vec); }

  reverse_iterator rbegin() { return reverse_iterator(end()); }

  reverse_iterator rend() { return reverse_iterator(begin()); }

  void reserve(size_t new_size_mem) {
    size_t i;
    if (new_size_mem > size_mem) {
      T* new_data_vec = alloc.allocate(new_size_mem);
      for (i = 0; i < size_vec; i++) {
        new_data_vec[i] = data_vec[i];
      }
      alloc.deallocate(data_vec);
      size_mem = new_size_mem;
      data_vec = new_data_vec;
    }
  }

  void resize(size_t new_size_vec) {
    if (new_size_vec > size_vec) {
      (*this).reserve(new_size_vec);
      size_vec = new_size_vec;
    } else {
      size_vec = new_size_vec;
    }
  }

  void resize(size_t new_size_vec, T val) {
    size_t i;
    if (new_size_vec > size_vec) {
      (*this).reserve(new_size_vec);
      size_t old_vec_size = size_vec;
      size_vec = new_size_vec;
      for (i = old_vec_size; i < size_vec; i++) {
        data_vec[i] = val;
      }
    } else {
      size_vec = new_size_vec;
    }
  }

  void push_back(T val) {
    if (size_vec < size_mem) {
      data_vec[size_vec] = val;
      size_vec++;
    } else {
      reserve(size_vec * 2);
      data_vec[size_vec] = val;
      size_vec++;
    }
  }

  T pop_back() {
    T res = data_vec[size_vec - 1];
    size_vec = size_vec - 1;
    return res;
  }

  template <class... ArgsT>
  void emplace_back(ArgsT&&... args) {
    if (size_vec < size_mem) {
      alloc.construct(data_vec + size_vec, args...);
      size_vec++;
    } else {
      int extra = 0;
      if (size_mem == 0) {
        extra = 1;
      }
      reserve(2 * size_mem + extra);
      alloc.construct(data_vec + size_vec, args...);
      size_vec++;
    }
  }

  ~My_vector() { alloc.deallocate(data_vec); }
};

#endif
