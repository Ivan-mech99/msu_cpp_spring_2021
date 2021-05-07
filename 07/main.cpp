#include <iostream>
#include <cassert>
#include <vector>
#include "My_vector.h"
using namespace std;
class Item {
 public:
  int a, b, c;
  Item() {
    a = 4;
    b = 5;
    c = 6;
  }
  Item(int a, int b, int c) : a(a), b(b), c(c) {}
};

void Push_back_test() {
  My_vector<double> vec;
  vector<double> test_vec;
  double begin1 = 0.1;
  int i;
  for (i = 0; i < 8; i++) {
    vec.push_back(i * begin1);
    test_vec.push_back(i * begin1);
  }
  for (i = 0; i < 8; i++) {
    assert(vec[i] == test_vec[i]);
  }
}

void Emplace_back_test() {
  My_vector<Item> x;
  x.emplace_back(1, 2, 3);
  assert((x[0].a == 1) && (x[0].b == 2) && (x[0].c == 3));
}

void Capacity_Size_Clear_Empty_test() {
  My_vector<int> vec;
  int i;
  for (i = 0; i < 4; i++) {
    vec.push_back(i);
  }
  assert(vec.capacity() == 8);
  assert(vec.size() == 4);
  vec.clear();
  assert(vec.size() == 0);
  assert(vec.empty());
}

void Begin_End_test() {
  My_vector<double> vec;
  vector<double> test_vec;
  double begin1 = 0.1;
  int i;
  for (i = 0; i < 10; i++) {
    vec.push_back(i * begin1);
    test_vec.push_back(i * begin1);
  }
  Iterator<double> t = vec.begin();
  assert(*t == 0);
  int ind = 0;
  while (t != vec.end()) {
    assert(*t == test_vec[ind]);
    ind++;
    ++t;
  }
  Iterator<double> t1 = vec.end();
  ind = 10;
  while (t != vec.begin()) {
    ind--;
    --t;
    assert(*t == test_vec[ind]);
  }
}

void Rbegin_Rend_test() {
  My_vector<double> vec;
  vector<double> test_vec;
  double begin1 = 0.1;
  int i;
  for (i = 0; i < 10; i++) {
    vec.push_back(i * begin1);
    test_vec.push_back(i * begin1);
  }
  reverse_iterator<Iterator<double>> t = vec.rbegin();
  assert(*t == 0.9);
  int ind = 9;
  while (t != vec.rend()) {
    assert(*t == test_vec[ind]);
    ind--;
    ++t;
  }
  reverse_iterator<Iterator<double>> t1 = vec.rend();
  ind = 0;
  while (t != vec.rbegin()) {
    --t;
    assert(*t == test_vec[ind]);
    ind++;
  }
}

void Resize_without_fill_test() {
  My_vector<int> vec;
  int i;
  for (i = 0; i < 8; i++) {
    vec.push_back(i);
  }
  assert(vec.size() == 8);
  vec.resize(10);
  for (i = 0; i < 8; i++) {
    assert(vec[i] == i);
  }
  assert(vec.size() == 10);
}

void Resize_with_fill_test() {
  My_vector<int> vec;
  int i;
  for (i = 0; i < 8; i++) {
    vec.push_back(i);
  }
  assert(vec.size() == 8);
  vec.resize(10, 599);
  for (i = 0; i < 8; i++) {
    assert(vec[i] == i);
  }
  assert(vec.size() == 10);
  assert(vec[8] == 599);
  assert(vec[9] == 599);
}

void Pop_back_test() {
  My_vector<int> vec;
  size_t i;
  for (i = 0; i < 8; i++) {
    vec.push_back(i);
  }
  assert(vec.size() == 8);
  int res = vec.pop_back();
  assert((res == 7) && (vec.size() == 7));
}

int main() {
  Push_back_test();
  Emplace_back_test();
  Capacity_Size_Clear_Empty_test();
  Begin_End_test();
  Rbegin_Rend_test();
  Resize_without_fill_test();
  Resize_with_fill_test();
  Pop_back_test();
  cout << "Success!" << endl;
  return 0;
}
