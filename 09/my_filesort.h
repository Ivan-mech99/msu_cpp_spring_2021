#ifndef H_MY_FILESORT
#define H_MY_FILESORT
#pragma once
#include <string>
#include <vector>
#include <thread>
#include <algorithm>
using std::string;
using std::vector;

void Test_file_make_func(string Filename, uint64_t file_size);
bool Is_right_order(string Filename, uint64_t file_size);
void inner_sort_left(uint64_t *data, size_t dat_amount,
                     vector<string> &temp_fnames, size_t ind);
void inner_sort_right(uint64_t *data, size_t dat_amount,
                      vector<string> &temp_fnames, size_t ind);
void sort_file(string input_fname, string output_fname);
void merge(vector<string> &temp_names, string output_fname);

#endif
