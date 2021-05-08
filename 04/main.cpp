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
  string str4 = "255578993477419401";
  string str5 = "456657234181699";
  string str6 = "255122336243237702";
  BigInt a1(str4);
  BigInt b1(str5);
  BigInt c1(str6);
  BigInt res = c1 + b1;
  cout << res << endl;
  assert(res == a1);
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
  string str4 = "255578993477419401";
  string str5 = "456657234181699";
  string str6 = "255122336243237702";
  BigInt a1(str4);
  BigInt b1(str5);
  BigInt test(str6);
  BigInt res = a1 - b1;
  cout << res << endl;
  assert(res == test);
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
  string str4 = "546123987";
  string str5 = "467987123";
  string str6 = "255578993477419401";
  BigInt a1(str4);
  BigInt b1(str5);
  BigInt test(str6);
  BigInt res = a1 * b1;
  cout << res << endl;
  assert(res == test);
}

void Move_const_test() {
  string str1 = "101200888664876954342123";
  BigInt a(str1);
  BigInt c(str1);
  BigInt b = std::move(a);
  assert(b == c);
  assert(a.is_null_ptr() && (a.get_length() == 0));
}

void Move_operator_test() {
  string str1 = "101200888664876954342123";
  string str2 = "23534698976544";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str1);
  BigInt d(str2);
  a = std::move(b);
  assert(b.is_null_ptr() && (b.get_length() == 0));
  assert(a == d);
}

void Zero_test() {
  string str1 = "101200888664876954342123";
  BigInt a(str1);
  string str2 = "1234";
  BigInt b(str2);
  BigInt c("0");
  BigInt res;
  BigInt res1;
  BigInt res2;
  res = a * c;
  res1 = a + res;
  assert(res1 == a);
  cout << res1 << endl;
  res2 = b + res;
  assert(res2 == b);
  cout << res2 << endl;
  res1 = a - res;
  assert(res1 == a);
  cout << res1 << endl;
  res2 = b - res;
  assert(res2 == b);
  cout << res2 << endl;
}

void Close_to_zero_test() {
  string str1 = "9";
  string str2 = "47";
  string str3 = "657123";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str3);
  string rs1 = "423";
  string rs2 = "56";
  string rs3 = "38";
  string rs4 = "657132";
  string rs5 = "657114";
  string rs6 = "5914107";
  BigInt test1(rs1);
  BigInt test2(rs2);
  BigInt test3(rs3);
  BigInt test4(rs4);
  BigInt test5(rs5);
  BigInt test6(rs6);
  BigInt res;
  res = a + b;
  assert(res == test2);
  cout << res << endl;
  res = a * b;
  assert(res == test1);
  cout << res << endl;
  res = b - a;
  assert(res == test3);
  cout << res << endl;
  res = c + a;
  assert(res == test4);
  cout << res << endl;
  res = c - a;
  assert(res == test5);
  cout << res << endl;
  res = c * a;
  assert(res == test6);
  cout << res << endl;
}

void Close_to_base_test() {
  string str1 = "1019";
  string str2 = "657123";
  BigInt a(str1);
  BigInt b(str2);
  string rs1 = "658142";
  string rs2 = "656104";
  string rs3 = "669608337";
  BigInt test1(rs1);
  BigInt test2(rs2);
  BigInt test3(rs3);
  BigInt res = a + b;
  assert(res == test1);
  cout << res << endl;
  res = b - a;
  assert(res == test2);
  cout << res << endl;
  res = a * b;
  assert(res == test3);
  cout << res << endl;
}

void Interesting_cases_test() {
  string str1 = "999999999999999999999";
  string str2 = "1000000000000000000000";
  string str3 = "1";
  string str4 = "0";
  string str6 = "1000";
  string str7 = "999";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str3);
  BigInt th(str6);
  BigInt th_9(str7);
  BigInt d = a + c;
  assert(d == b);
  cout << d << endl;
  BigInt f = b - c;
  assert(f == a);
  cout << f << endl;
  BigInt g = th - th_9;
  assert(g == c);
  cout << g << endl;
  g = th * th_9;
  assert(g == BigInt("999000"));
  cout << g << endl;
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
  Move_const_test();
  Move_operator_test();
  Zero_test();
  Close_to_zero_test();
  Close_to_base_test();
  Interesting_cases_test();
  return 0;
}

