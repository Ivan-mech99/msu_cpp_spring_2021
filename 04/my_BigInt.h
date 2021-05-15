#ifndef H_MY_BIGINT
#define H_MY_BIGINT
#include <string>
using std::string;
class BigInt {
 public:
  int *num_data;
  bool sign;
  int num_len;

 public:
  BigInt();
  int find_len(int num) const;
  int find_len_help(int &num, int &l) const;
  int collect_remainders(int &num) const;
  BigInt(int num);
  BigInt(int l, int arg);
  BigInt(string number);
  void show();
  bool operator==(const BigInt &a) const;
  bool operator!=(const BigInt &b) const;
  bool operator>(const BigInt &b) const;
  bool operator<(const BigInt &b) const;
  bool operator>=(const BigInt &b) const;
  bool operator<=(const BigInt &b) const;
  BigInt(const BigInt &obj);
  BigInt &operator=(const BigInt &b);
  BigInt summar(const BigInt &a, const BigInt &b) const;
  BigInt differ(const BigInt &a, const BigInt &b) const;
  ~BigInt();
  BigInt mult(const BigInt &a, const BigInt &b) const;
  BigInt operator-();
  BigInt operator+(const BigInt &b) const;
  BigInt operator-(const BigInt &b) const;
  BigInt operator*(const BigInt &b) const;
  BigInt operator+(const int &b) const;
  BigInt operator-(const int &b) const;
  BigInt operator*(const int &b) const;
  friend std::ostream &operator<<(std::ostream &cc, BigInt &b);
  BigInt(BigInt &&other);
  BigInt &operator=(BigInt &&other);
  int get_length() const;
  bool is_null_ptr() const;
};

#endif
