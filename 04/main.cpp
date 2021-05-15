#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include "my_BigInt.h"
using namespace std;

void Equality_test() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  string str3 = "-101200888664876954342123";
  string str4 = "1000";
  string str5 = "-1000";
  string str6 = "0";
  BigInt a(str1);
  BigInt b(str1);
  BigInt c(str2);
  BigInt d(str3);
  BigInt zer(str6);
  BigInt zer1(str6);
  BigInt th(str4);
  BigInt mth(str5);
  bool res1 = (a == b);
  bool res2 = (a == c);
  assert(res1 && !res2);
  cout << "Zero equality test" << endl;
  res1 = (zer == zer1);
  res2 = (zer == a);
  bool res3 = (zer == d);
  bool res4 = (zer == th);
  bool res5 = (zer == mth);
  assert(res1 && (!res2) && (!res3) && (!res4) && (!res5));
  cout << "Done!" << endl;
}

void Unequality_test() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  string str3 = "-101200888664876954342123";
  string str4 = "1000";
  string str5 = "-1000";
  string str6 = "0";
  BigInt a(str1);
  BigInt b(str1);
  BigInt c(str2);
  BigInt d(str3);
  BigInt zer(str6);
  BigInt zer1(str6);
  BigInt th(str4);
  BigInt mth(str5);
  bool res1 = (a != b);
  bool res2 = (a != c);
  assert(!res1 && res2);
  cout << "Zero Unequality test" << endl;
  res1 = (zer != zer1);
  res2 = (zer != a);
  bool res3 = (zer != d);
  bool res4 = (zer != th);
  bool res5 = (zer != mth);
  assert((!res1) && res2 && res3 && res4 && res5);
  cout << "Done!" << endl;
}

void Bigger_test() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  string str3 = "-101200888664876954342123";
  string str4 = "-101200988664876954342123";
  string str5 = "0";
  string thousand = "1000";
  string m_thousand = "-1000";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str3);
  BigInt d(str4);
  BigInt zer(str5);
  BigInt th(thousand);
  BigInt mth(m_thousand);
  bool res1 = (a > b);
  bool res2 = (b > a);
  bool res3 = (c > d);
  bool res4 = (d > c);
  bool res5 = (a > d);
  bool res6 = (d > a);
  assert((!res1) && res2 && res3 && (!res4) && res5 && (!res6));
  cout << "Bigger zero test" << endl;
  res1 = (a > zer);
  res2 = (zer > c);
  res3 = (th > zer);
  res4 = (zer > mth);
  assert(res1 && res2 && res3 && res4);
  cout << "Done!" << endl;
}

void Smaller_test() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  string str3 = "-101200888664876954342123";
  string str4 = "-101200988664876954342123";
  string str5 = "0";
  string thousand = "1000";
  string m_thousand = "-1000";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str3);
  BigInt d(str4);
  BigInt zer(str5);
  BigInt th(thousand);
  BigInt mth(m_thousand);
  bool res1 = (a < b);
  bool res2 = (b < a);
  bool res3 = (c < d);
  bool res4 = (d < c);
  bool res5 = (a < d);
  bool res6 = (d < a);
  assert(res1 && (!res2) && (!res3) && res4 && (!res5) && res6);
  cout << "Smaller zero test:" << endl;
  res1 = (zer < a);
  res2 = (c < zer);
  res3 = (zer < th);
  res4 = (mth < zer);
  assert(res1 && res2 && res3 && res4);
  cout << "Done!" << endl;
}

void Bigger_or_less() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  string str3 = "0";
  string str4 = "-101200988664876954342123";
  string thousand = "1000";
  string m_thousand = "-1000";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str2);
  BigInt zer(str3);
  BigInt zer1(str3);
  BigInt th(thousand);
  BigInt mth(m_thousand);
  BigInt neg(str4);
  bool res1 = (b >= a);
  bool res2 = (b >= c);
  assert(res1 && res2);
  cout << "Bigger or less zero test" << endl;
  res1 = (a >= zer);
  res2 = (zer >= neg);
  bool res3 = (th >= zer);
  bool res4 = (zer >= mth);
  bool res5 = (zer >= zer1);
  assert(res1 && res2 && res3 && res4 && res5);
  cout << "Done!" << endl;
}

void Smaller_or_less() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  string str3 = "0";
  string str4 = "-101200988664876954342123";
  string thousand = "1000";
  string m_thousand = "-1000";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str2);
  BigInt zer(str3);
  BigInt zer1(str3);
  BigInt th(thousand);
  BigInt mth(m_thousand);
  BigInt neg(str4);
  bool res1 = (a <= b);
  bool res2 = (b <= c);
  assert(res1 && res2);
  cout << "Smaller or less zero test" << endl;
  res1 = (zer <= a);
  res2 = (neg <= zer);
  bool res3 = (zer <= th);
  bool res4 = (mth <= zer);
  bool res5 = (zer1 <= zer);
  assert(res1 && res2 && res3 && res4 && res5);
  cout << "Done!" << endl;
}

void Assignment() {
  string str1 = "101200888664876954342123";
  string str2 = "101200988664876954342123";
  BigInt a(str1);
  BigInt b(str2);
  b = a;
  stringstream stream_a;
  stringstream stream_b;
  stream_a << a;
  stream_b << b;
  bool res = (stream_a.str() == stream_b.str());
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
  cout << str3 << endl;
  stringstream cs;
  stringstream fs;
  cs << c;
  fs << f;
  assert(cs.str() == str3 && str3 == fs.str());
  cs.str("");
  string str4 = "255578993477419401";
  string str5 = "456657234181699";
  string str6 = "255122336243237702";
  BigInt b1(str5);
  BigInt c1(str6);
  BigInt res = c1 + b1;
  cout << res << endl;
  cs << res;
  assert(cs.str() == str4);
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
  cout << str3 << endl;
  stringstream cs;
  stringstream fs;
  cs << c;
  fs << f;
  assert(cs.str() == str3 && fs.str() == str3);
  string str4 = "255578993477419401";
  string str5 = "456657234181699";
  string str6 = "255122336243237702";
  BigInt a1(str4);
  BigInt b1(str5);
  BigInt res = a1 - b1;
  cout << res << endl;
  cs.str("");
  cs << res;
  assert(cs.str() == str6);
}

void Multiplication_test() {
  int z = 63;
  string str1 = "2019";
  string str2 = "63";
  string str3 = "127197";
  string strb4 = "123456789123654";
  string strb5 = "111222356981121";
  string strb = "13731155071654021610612536134";
  BigInt a(str1);
  BigInt b(str2);
  BigInt big1(strb4);
  BigInt big2(strb5);
  BigInt c = a * b;
  BigInt f = a * z;
  cout << str3 << endl;
  stringstream cs;
  stringstream fs;
  cs << c;
  fs << f;
  assert(cs.str() == str3 && fs.str() == str3);
  string str4 = "546123987";
  string str5 = "467987123";
  string str6 = "255578993477419401";
  BigInt a1(str4);
  BigInt b1(str5);
  BigInt res = a1 * b1;
  cout << res << endl;
  cs.str("");
  cs << res;
  assert(cs.str() == str6);
  cout << "Big numbers multiplication test" << endl;
  BigInt bigmult = big1 * big2;
  cs.str("");
  cs << bigmult;
  cout << bigmult << endl;
  assert(cs.str() == strb);
  cout << "Done!" << endl;
}

void Move_const_test() {
  string str1 = "101200888664876954342123";
  BigInt a(str1);
  BigInt b = std::move(a);
  stringstream bs;
  bs << b;
  assert(bs.str() == str1);
  assert(a.is_null_ptr() && (a.get_length() == 0));
}

void Move_operator_test() {
  string str1 = "101200888664876954342123";
  string str2 = "23534698976544";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str1);
  stringstream as;
  a = std::move(b);
  assert(b.is_null_ptr() && (b.get_length() == 0));
  as << a;
  assert(as.str() == str2);
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
  stringstream as;
  res = a * c;
  res1 = a + res;
  as << res1;
  assert(as.str() == str1);
  cout << res1 << endl;
  res2 = b + res;
  as.str("");
  as << res2;
  assert(as.str() == str2);
  cout << res2 << endl;
  res1 = a - res;
  as.str("");
  as << res1;
  assert(as.str() == str1);
  cout << res1 << endl;
  res2 = b - res;
  as.str("");
  as << res2;
  assert(as.str() == str2);
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
  BigInt res;
  res = a + b;
  stringstream as;
  as << res;
  assert(as.str() == rs2);
  cout << res << endl;
  res = a * b;
  as.str("");
  as << res;
  assert(as.str() == rs1);
  cout << res << endl;
  res = b - a;
  as.str("");
  as << res;
  assert(as.str() == rs3);
  cout << res << endl;
  res = c + a;
  as.str("");
  as << res;
  assert(as.str() == rs4);
  cout << res << endl;
  res = c - a;
  as.str("");
  as << res;
  assert(as.str() == rs5);
  cout << res << endl;
  res = c * a;
  as.str("");
  as << res;
  assert(as.str() == rs6);
  cout << res << endl;
}

void Update_close_to_base_test() {
  string th = "1000";
  string mth = "-1000";
  string str1 = "555854698321";
  string str2 = "985674123";
  string str3 = "555854697321";
  string str4 = "648";
  string str5 = "352";
  string str6 = "985674123000";
  string str7 = "-985674123000";
  string one = "1";
  stringstream as;
  BigInt a(str1);
  BigInt ths(th);
  BigInt mths(mth);
  BigInt c(str3);
  BigInt res1 = a + ths;
  string ans1 = "555854699321";
  cout << res1 << endl;
  as << res1;
  assert(as.str() == ans1);
  as.str("");
  res1 = a - ths;
  as << res1;
  cout << res1 << endl;
  assert(as.str() == str3);
  BigInt b(str2);
  res1 = b * th;
  as.str("");
  as << res1;
  cout << res1 << endl;
  assert(as.str() == str6);
  res1 = b * mth;
  as.str("");
  as << res1;
  cout << res1 << endl;
  assert(as.str() == str7);
  res1 = a - c;
  as.str("");
  as << res1;
  cout << res1 << endl;
  assert(as.str() == th);
  BigInt d(str4);
  BigInt e(str5);
  res1 = d + e;
  as.str("");
  as << res1;
  cout << res1 << endl;
  assert(as.str() == th);
  BigInt one1(one);
  res1 = ths * one1;
  as.str("");
  as << res1;
  cout << res1 << endl;
  assert(as.str() == th);
  res1 = mths * one1;
  as.str("");
  as << res1;
  cout << res1 << endl;
  assert(as.str() == mth);
}

void Interesting_cases_test() {
  string str1 = "999999999999999999999";
  string str2 = "1000000000000000000000";
  string str3 = "1";
  string str4 = "0";
  string str6 = "1000";
  string str7 = "999";
  string str8 = "999000";
  BigInt a(str1);
  BigInt b(str2);
  BigInt c(str3);
  BigInt th(str6);
  BigInt th_9(str7);
  stringstream as;
  BigInt d = a + c;
  as << d;
  assert(as.str() == str2);
  cout << d << endl;
  BigInt f = b - c;
  as.str("");
  as << f;
  assert(as.str() == str1);
  cout << f << endl;
  as.str("");
  BigInt g = th - th_9;
  as << g;
  assert(as.str() == str3);
  cout << g << endl;
  g = th * th_9;
  as.str("");
  as << g;
  assert(as.str() == str8);
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
  Interesting_cases_test();
  Update_close_to_base_test();
  return 0;
}
