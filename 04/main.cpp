#include <iostream>
#include <string>
#include <cassert>
#include "my_BigInt.h"
using namespace std;

void Equality_test() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  BigInt a(str1);
  BigInt b(str1);
  BigInt c(str2);
  bool res1 = (a == b);
  bool res2 = (a == c);
  assert(res1 && !res2);
}

void Unequality_test() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  BigInt a(str1);
  BigInt b(str1);
  BigInt c(str2);
  bool res1 = (a != b);
  bool res2 = (a != c);
  assert(!res1 && res2);
}

void Bigger_test() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  string str3 = "-101200888664876954342123";
  string str4 = "-101200988664876954342123";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str3);
  BigInt d(str4);
  bool res1 = (a > b);
  bool res2 = (b > a);
  bool res3 = (c > d);
  bool res4 = (d > c);
  bool res5 = (a > d);
  bool res6 = (d > a);
  assert((!res1) && res2 && res3 && (!res4) && res5 && (!res6));
}

void Smaller_test() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  string str3 = "-101200888664876954342123";
  string str4 = "-101200988664876954342123";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str3);
  BigInt d(str4);
  bool res1 = (a < b);
  bool res2 = (b < a);
  bool res3 = (c < d);
  bool res4 = (d < c);
  bool res5 = (a < d);
  bool res6 = (d < a);
  assert(res1 && (!res2) && (!res3) && res4 && (!res5) && res6);
}

void Bigger_or_less() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str2);
  bool res1 = (b >= a);
  bool res2 = (b >= c);
  assert(res1 && res2);
}

void Smaller_or_less() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str2);
  bool res1 = (a <= b);
  bool res2 = (b <= c);
  assert(res1 && res2);
}

void Assignment() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  BigInt a(str1);
  BigInt b(str2);
  b = a;
  bool res = (a == b);
  assert(res);
}

void Sum_test() {
  string str1 = "2019";
  string str2 = "648";
  string str3 = "2667";
  int z = 648;
  BigInt a(str1);
  BigInt b(str2);
  BigInt c = a + b;
  BigInt f = a + z;
  BigInt d(str3);
  cout << d << endl;
  assert(c == d && d == f);
}

void Difference_test() {
  string str1 = "2019";
  string str2 = "648";
  string str3 = "1371";
  int z = 648;
  BigInt a(str1);
  BigInt b(str2);
  BigInt c = a - b;
  BigInt f = a - z;
  BigInt d(str3);
  cout << d << endl;
  assert(c == d && f == d);
}

void Multiplication_test() {
  int z = 63;
  string str1 = "2019";
  string str2 = "63";
  string str3 = "127197";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c = a * b;
  BigInt f = a * z;
  BigInt d(str3);
  cout << d << endl;
  assert(c == d && f == d);
}

int main() {
  Equality_test();
  Unequality_test();
  Bigger_test();
  Smaller_test();
  Bigger_or_less();
  Smaller_or_less();
  Assignment();
  Sum_test();
  Difference_test();
  Multiplication_test();
  getchar();
  return 0;
}

