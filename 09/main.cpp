#include <iostream>
#include <fstream>
#include <thread>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <cassert>
#include "my_filesort.h"
using namespace std;

void Basic_test() {
  bool res;
  string data_filename = "test.bin";
  string result_filename = "output.bin";
  uint64_t fsize = 1000000;
  Test_file_make_func(data_filename, fsize);
  sort_file(data_filename, result_filename);
  res = Is_right_order(result_filename, fsize);
  assert(res == true);
}

int main() {
  Basic_test();
  cout << "Success!" << endl;
  return 0;
}
