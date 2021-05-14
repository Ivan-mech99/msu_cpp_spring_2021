#include <iostream>
#include <cassert>
#include <thread>
#include <ctime>
#include "my_pool.h"
using std::cout;
using std::endl;
uint64_t num_iter = 1000;

int oper1(int obj) {
  uint64_t i;
  for (i = 0; i < num_iter; i++) {
    obj = obj + 1;
    obj = obj - 1;
  }
  obj = obj + 1;
  return obj;
}

int oper2(int obj) {
  uint64_t i;
  for (i = 0; i < num_iter; i++) {
    obj = obj * 2;
    obj = obj / 2;
  }
  obj = obj * 2;
  return obj;
}

int oper3(int obj) {
  uint64_t i;
  for (i = 0; i < num_iter; i++) {
    obj = obj + 3;
    obj = obj - 3;
  }
  obj = obj - 3;
  return obj;
}

int oper4(int obj) {
  uint64_t i;
  for (i = 0; i < num_iter; i++) {
    obj = obj * 3;
    obj = obj / 3;
  }
  obj = obj * 3;
  return obj;
}

struct A {};

void foo(const A&) {}

void Basic_test() {
  ThreadPool pool(8);

  auto task1 = pool.exec(foo, A());
  task1.get();

  auto task2 = pool.exec([]() { return 1; });
  assert(task2.get() == 1);
}

void Test_mul_op() {
  int i;
  ThreadPool pool(4);
  int res = 1;
  int start = clock();
  for (i = 0; i < 4; i++) {
    res = pool.exec(oper1, res).get();
    cout << res << ' ';
    res = pool.exec(oper2, res).get();
    cout << res << ' ';
    res = pool.exec(oper3, res).get();
    cout << res << ' ';
    res = pool.exec(oper4, res).get();
    cout << res << endl;
  }
  int end = clock();
  int t = (end - start);
  cout << "Time: " << t << endl;
  cout << "Result: " << res << endl;
  assert(res == 519);
}

int main() {
  Basic_test();
  Test_mul_op();
  cout << "Success!" << endl;
  return 0;
}
