#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include <algorithm>
#include "my_filesort.h"

using std::string;
using std::ofstream;
using std::ifstream;
using std::cout;
using std::endl;
using std::ios;
using std::vector;
using std::sort;
using std::to_string;
using std::thread;

size_t memory_amount = 1024 * 8;

void Test_file_make_func(string Filename, uint64_t file_size) {
  uint64_t i;
  ofstream File(Filename, ios::binary | ios::out);
  uint64_t fsize = file_size;
  uint64_t num;
  for (i = 0; i < fsize; i++) {
    num = uint64_t(std::rand() % fsize);
    File.write((char *)&num, sizeof(uint64_t));
  }
  File.close();
}

bool Is_right_order(string Filename, uint64_t file_size) {
  ifstream File(Filename, ios::binary | ios::in);
  uint64_t prev = 0;
  uint64_t cur;
  uint64_t ind = 0;
  while (ind < file_size) {
    File.read((char *)&cur, sizeof(uint64_t));
    if (cur >= prev) {
      prev = cur;
      ind = ind + 1;
    } else {
      return false;
    }
  }
  cout << "Correctly sorted file" << endl;
  return true;
}

void inner_sort_left(uint64_t *data, size_t dat_amount,
                     vector<string> &temp_fnames, size_t ind) {
  size_t i;
  size_t elem_size = sizeof(uint64_t);
  sort(data, data + (dat_amount / 2));
  ofstream File(temp_fnames[ind], ios::binary | ios::out);
  for (i = 0; i < dat_amount / 2; i++) {
    File.write((char *)(&data[i]), elem_size);
  }
  File.close();
}

void inner_sort_right(uint64_t *data, size_t dat_amount,
                      vector<string> &temp_fnames, size_t ind) {
  size_t i;
  size_t elem_size = sizeof(uint64_t);
  sort(data + (dat_amount / 2), data + dat_amount);
  ofstream File;
  File.open(temp_fnames[ind], ios::binary | ios::out);
  for (i = dat_amount / 2; i < dat_amount; i++) {
    File.write((char *)(&data[i]), elem_size);
  }
  File.close();
}

void merge(vector<string> &temp_names, string output_fname) {
  size_t name_ind = temp_names.size();
  size_t i, j;
  size_t sz = sizeof(uint64_t);
  uint64_t cur_elem;
  for (i = 1; i < name_ind; i++) {
    uint64_t *data = new uint64_t[memory_amount / 2];
    ifstream File1(temp_names[i], ios::binary | ios::in);
    File1.read((char *)data, memory_amount / 2 * sz);
    auto size_read = File1.gcount() / sz;
    File1.close();
    ifstream File2(temp_names[i - 1], ios::binary | ios::in);
    File2.read((char *)&cur_elem, sz);
    j = 0;
    if (i == name_ind - 1) {
      temp_names[i] = output_fname;
    }
    ofstream result(temp_names[i], ios::binary | ios::out);
    while ((j < size_read) && (!File2.eof())) {
      if (cur_elem <= data[j]) {
        result.write((char *)(&cur_elem), sz);
        File2.read((char *)(&cur_elem), sz);

      } else {
        result.write((char *)(&data[j]), sz);
        j++;
      }
    }
    if (File2.eof()) {
      result.write((char *)&data[j], sz);
    }
    while (!File2.eof()) {
      result.write((char *)(&cur_elem), sz);
      File2.read((char *)(&cur_elem), sz);
    }
    File2.close();
    result.close();
    if (i == name_ind - 1) {
      temp_names[i] = to_string(name_ind - 1);
    }
    delete[] data;
  }
  for (i = 0; i < temp_names.size(); i++) {
    remove(temp_names[i].c_str());
  }
  remove(to_string(int(temp_names.size()) - 2).c_str());
}

void sort_file(string input_fname, string output_fname) {
  ifstream File(input_fname, ios::binary | ios::in);
  vector<string> temp_names;
  size_t name_ind = 0;
  size_t elem_size = sizeof(uint64_t);
  uint64_t *data = new uint64_t[memory_amount];
  while (!File.eof()) {
    File.read((char *)data, memory_amount * elem_size);
    auto read_amount = File.gcount();
    if (read_amount > 0) {
      name_ind = name_ind + 2;
      temp_names.push_back(to_string(name_ind - 1));
      temp_names.push_back(to_string(name_ind - 2));
      auto data_amount = File.gcount() / elem_size;
      auto thread1 = thread(inner_sort_left, data, data_amount,
                            std::ref(temp_names), name_ind - 1);
      auto thread2 = thread(inner_sort_right, data, data_amount,
                            std::ref(temp_names), name_ind - 2);
      thread1.join();
      thread2.join();
    }
  }
  delete[] data;
  merge(temp_names, output_fname);
}
