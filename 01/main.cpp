#include <iostream>
#include <cstdlib>
#include <string>
#include <cassert>
#include "my_allocator.h"
using std::cout;
using std::endl;
using std::string;

void Alloc_first_block() {
  Allocator a;
  a.makeAllocator(30);
  char *a1;
  a1 = a.alloc(30);
  assert(a1 != nullptr);
}

void Alloc_3_blocks() {
  Allocator a;
  int l1, l2, l3;
  l1 = 10;
  l2 = 7;
  l3 = 5;
  a.makeAllocator(30);
  char *a1;
  a1 = a.alloc(l1);
  char *a2;
  a2 = a.alloc(l2);
  char *a3;
  a3 = a.alloc(l3);
  assert(a2 - a1 == l1 && a3 - a2 == l2);
}

void Alloc_too_big_block() {
  char *a4;
  Allocator a;
  a.makeAllocator(30);
  char *a1;
  a1 = a.alloc(25);
  char *a2;
  a2 = a.alloc(6);
  assert(a2 == nullptr && a.free_mem_show() == 5);
}

void Alloc_zero_len_block() {
  char *a4;
  Allocator a;
  a.makeAllocator(30);
  char *a1;
  a1 = a.alloc(25);
  char *a2;
  a2 = a.alloc(0);
  assert(a2 == nullptr && a.free_mem_show() == 5);
}

void Filling_blocks_with_letters() {
  Allocator a;
  int l1, l2, l3;
  l1 = 10;
  l2 = 7;
  l3 = 5;
  a.makeAllocator(30);
  char *a1;
  a1 = a.alloc(l1);
  char *a2;
  a2 = a.alloc(l2);
  char *a3;
  a3 = a.alloc(l3);
  string ans = "";
  int i;
  for (i = 0; i < l1; i++) {
    *(a1 + i) = 'a';
    ans = ans + 'a';
  }
  for (i = 0; i < l2; i++) {
    *(a2 + i) = 'b';
    ans = ans + 'b';
  }
  for (i = 0; i < l3; i++) {
    *(a3 + i) = 'c';
    ans = ans + 'c';
  }
  string res = "";
  for (i = 0; i < l1 + l2 + l3; i++) res = res + *(a1 + i);
  assert(res == ans);
}

void Reset_test() {
  Allocator a;
  int l1, l2, l3;
  l1 = 10;
  l2 = 7;
  l3 = 5;
  a.makeAllocator(30);
  char *a1;
  a1 = a.alloc(l1);
  char *a2;
  a2 = a.alloc(l2);
  char *a3;
  a3 = a.alloc(l3);
  int i;
  for (i = 0; i < l1; i++) {
    *(a1 + i) = 'a';
  }
  for (i = 0; i < l2; i++) {
    *(a2 + i) = 'b';
  }
  for (i = 0; i < l3; i++) {
    *(a3 + i) = 'c';
  }
  a.reset();
  assert(a.free_mem_show() == 30);
}

void Alloc_after_reset() {
  Allocator a;
  int l1, l2, l3;
  l1 = 10;
  l2 = 7;
  l3 = 5;
  a.makeAllocator(30);
  char *a1;
  a1 = a.alloc(l1);
  char *a2;
  a2 = a.alloc(l2);
  char *a3;
  a3 = a.alloc(l3);
  int i;
  for (i = 0; i < l1; i++) {
    *(a1 + i) = 'a';
  }
  for (i = 0; i < l2; i++) {
    *(a2 + i) = 'b';
  }
  for (i = 0; i < l3; i++) {
    *(a3 + i) = 'c';
  }
  a.reset();
  int l4 = 13;
  char *a6;
  a6 = a.alloc(l4);
  string ans = "";
  string res = "";
  for (i = 0; i < l4; i++) {
    *(a1 + i) = 'd';
    ans = ans + 'd';
  }
  for (i = 0; i < l4; i++) res = res + *(a1 + i);
  assert(res == ans);
}

void Many_MakeAllocs() {
  Allocator a;
  a.makeAllocator(30);
  a.makeAllocator(60);
  int a2 = a.is_null_ptr();
  size_t state2 = a.mem_show();
  a.makeAllocator(90);
  size_t state3 = a.mem_show();
  int a3 = a.is_null_ptr();
  assert(state3 == 90 && state2 == 60 && (!a2) && (!a3));
}

void Boundary_conditions_test() {
  Allocator a;
  a.makeAllocator(10);
  char *a1 = a.alloc(10);
  int state1 = (a1 != nullptr);
  char *a2 = a.alloc(1);
  int state2 = (a2 == nullptr);
  a.reset();
  char *a3 = a.alloc(10);
  int state3 = (a3 != nullptr);
  assert(state1 && state2 && state3);
}

int main() {
  Alloc_first_block();
  Alloc_3_blocks();
  Alloc_too_big_block();
  Alloc_zero_len_block();
  Filling_blocks_with_letters();
  Reset_test();
  Alloc_after_reset();
  Many_MakeAllocs();
  Boundary_conditions_test();
  cout << "Success! " << endl;
  return 0;
}
