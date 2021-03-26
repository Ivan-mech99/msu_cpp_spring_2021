#include <iostream>
#include <cstdlib>
#include "my_allocator.h"
using std::cout;
using std::endl;

Allocator::Allocator() {
  size_t mem_amount = 0;
  size_t free_mem_amount = 0;
  char *mem_begin = nullptr;
  is_first_makeAlloc = 0;
}

Allocator::~Allocator() { delete[] mem_begin; }

void Allocator::makeAllocator(size_t maxSize) {
  if (is_first_makeAlloc == 0) {
    mem_amount = maxSize;
    free_mem_amount = maxSize;
    mem_begin = new char[maxSize];
    is_first_makeAlloc = 1;
  } else {
    delete[] mem_begin;
    mem_amount = maxSize;
    free_mem_amount = maxSize;
    mem_begin = new char[maxSize];
    is_first_makeAlloc = 1;
  }
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
