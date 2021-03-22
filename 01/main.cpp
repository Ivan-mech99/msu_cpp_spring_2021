#include <iostream>
#include <cstdlib>
#include "class.h"
using std::cout;
using std::endl;

int main() {
  Allocator a;
  int l1, l2, l3;
  l1 = 10;
  l2 = 7;
  l3 = 5;
  a.makeAllocator(30);
  cout << "\nTest1: is memory allocated after alloc?" << endl;
  char *a1;
  a1 = a.alloc(l1);
  if (a1 != nullptr)
    cout << "+" << endl;
  else
    cout << "-" << endl;
  cout << "\nTest2: allocate more blocks and check their lengths:" << endl;
  char *a2;
  a2 = a.alloc(l2);
  char *a3;
  a3 = a.alloc(l3);
  if (a2 - a1 == l1 && a3 - a2 == l2)
    cout << "+" << endl;
  else
    cout << "-" << endl;
  cout << "\nTest3: creating a bigger block than allowed:" << endl;
  char *a4;
  a4 = a.alloc(50);
  if (a4 == nullptr)
    cout << "+" << endl;
  else
    cout << "-" << endl;
  cout << "\nTest4: Trying to create block with zeros size (nothing must "
          "change):"
       << endl;
  cout << "Before trying: " << endl;
  a.show_info();
  char *a5;
  a5 = a.alloc(0);
  cout << "After trying to create:" << endl;
  a.show_info();
  cout << "\nTest5: Filling blocks with letters: " << endl;
  int i;
  for (i = 0; i < l1; i++) *(a1 + i) = 'a';
  for (i = 0; i < l2; i++) *(a2 + i) = 'b';
  for (i = 0; i < l3; i++) *(a3 + i) = 'c';
  for (i = 0; i < l1 + l2 + l3; i++) cout << *(a1 + i);
  cout << endl;
  cout << "\nTest6: reset" << endl;
  cout << "Before reset:" << endl;
  a.show_info();
  a.reset();
  cout << "After reset:" << endl;
  a.show_info();
  cout << "\nTest7: alloc after reset" << endl;
  int l4 = 13;
  char *a6;
  a6 = a.alloc(l4);
  for (i = 0; i < l4; i++) *(a1 + i) = 'd';
  for (i = 0; i < l4; i++) cout << *(a1 + i);
  cout << endl;
  return 0;
}
