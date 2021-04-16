#ifndef H_MY_BIGINT
#define H_MY_BIGINT
#include <string>
using std::string;
class BigInt {
  int *num_data;
  bool sign;
  int num_len;

 public:
  BigInt();
  int find_len(int num);
  int find_len_help(int &num, int &l);
  int collect_remainders(int &num);
  BigInt(int num);
  BigInt(int l, int arg);
  BigInt(string number);
  void show();
  bool operator==(const BigInt &a);
  bool operator!=(const BigInt &b);
  bool operator>(const BigInt &b);
  bool operator<(const BigInt &b);
  bool operator>=(const BigInt &b);
  bool operator<=(const BigInt &b);
  BigInt(const BigInt &obj);
  BigInt &operator=(const BigInt &b);
  BigInt summar(const BigInt &a, const BigInt &b);
  BigInt differ(const BigInt &a, const BigInt &b);
  ~BigInt();
  BigInt mult(const BigInt &a, const BigInt &b);
  BigInt operator-();
  BigInt operator+(const BigInt &b);
  BigInt operator-(const BigInt &b);
  BigInt operator*(const BigInt &b);
  BigInt operator+(const int &b);
  BigInt operator-(const int &b);
  BigInt operator*(const int &b);
  friend std::ostream &operator<<(std::ostream &cc, BigInt &b);
};

#endif
