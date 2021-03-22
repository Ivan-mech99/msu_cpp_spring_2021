#include <iostream>
#include <cstdlib>
#include "class.h"
using std::cout;
using std::endl;

Allocator::Allocator() { cout << "Created allocator" << endl; }

Allocator::~Allocator() {
  delete[] mem_begin;
  cout << "Destroyed allocator" << endl;
}

void Allocator::makeAllocator(size_t maxSize) {
  mem_amount = maxSize;
  free_mem_amount = maxSize;
  mem_begin = new char[maxSize];
}

char *Allocator::alloc(size_t size) {
  char *res = nullptr;
  if (free_mem_amount >= size && size > 0) {
    res = (mem_begin + mem_amount - free_mem_amount);
    free_mem_amount = free_mem_amount - size;
  }
  return res;
}

void Allocator::reset() { free_mem_amount = mem_amount; }

void Allocator::show_info() {
  cout << "mem_amount: " << mem_amount << endl;
  cout << "free_mem_amount: " << free_mem_amount << endl;
  if (mem_begin == nullptr)
    cout << "nullptr" << endl;
  else
    cout << "not nullptr" << endl;
}
