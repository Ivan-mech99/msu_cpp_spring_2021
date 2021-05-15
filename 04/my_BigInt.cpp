#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "my_BigInt.h"

using std::cout;
using std::endl;
using std::string;
BigInt::BigInt() {
  num_data = new int[1];
  num_data[0] = 0;
  sign = true;
  num_len = 1;
}

BigInt::BigInt(int l, int arg) {
  int i;
  num_data = new int[l];
  for (i = 0; i < l; i++) {
    num_data[i] = arg;
  }
  sign = true;
  num_len = l;
}

int BigInt::find_len(int num) const {
  int l = 0;
  int cur_num = num;
  do {
    cur_num = find_len_help(cur_num, l);
  } while (cur_num != 0);
  return l;
}

int BigInt::find_len_help(int &num, int &l) const {
  num = (num - (num % 1000)) / 1000;
  l++;
  return num;
}

int BigInt::collect_remainders(int &num) const {
  int res = num % 1000;
  num = (num - (num % 1000)) / 1000;
  return res;
}

BigInt::BigInt(int num) {
  int cur_num = abs(num);
  num_len = find_len(cur_num);
  if (num >= 0) {
    sign = true;
  } else {
    sign = false;
  }
  int i;
  num_data = new int[num_len];
  for (i = 0; i < num_len; i++) {
    num_data[i] = collect_remainders(cur_num);
  }
}

BigInt::BigInt(string number) {
  string inner_string = "";
  int num_len_temp;
  int i;
  int temp;
  if (number[0] == '-') {
    sign = false;
    num_len_temp = int(number.length()) - 1;
    for (i = 1; i < int(number.length()); i++) {
      inner_string = inner_string + number[i];
    }
  } else {
    sign = true;
    num_len_temp = int(number.length());
    inner_string = number;
  }
  num_len = inner_string.length() / 3;
  if (inner_string.length() % 3 != 0) {
    num_len++;
  }
  num_data = new int[num_len];
  int j = 0;
  int k = -1;
  for (i = inner_string.length() - 1; i >= 0; i--) {
    temp = 0;
    if (j % 3 == 0) {
      k = k + 1;
      temp = temp + (inner_string[i] - '0');
      if (i - 1 >= 0) {
        temp = temp + 10 * (inner_string[i - 1] - '0');
      }
      if (i - 2 >= 0) {
        temp = temp + 100 * (inner_string[i - 2] - '0');
      }
      num_data[k] = temp;
    }
    j++;
  }
}

void BigInt::show() {
  int i;
  for (i = num_len - 1; i >= 0; i--) {
    if (num_data[i] == 0 && i != num_len - 1) {
      cout << "000";
    } else if (num_data[i] / 10 == 0 && i != num_len - 1) {
      cout << "00" << num_data[i];
    } else if (num_data[i] / 100 == 0 && i != num_len - 1) {
      cout << "0" << num_data[i];
    } else {
      cout << num_data[i];
    }
  }
  cout << endl;
}

bool BigInt::operator==(const BigInt &b) const {
  if (sign != b.sign) {
    return false;
  }
  if (num_len != b.num_len) {
    return false;
  }
  int i;
  for (i = 0; i < num_len; i++) {
    if (num_data[i] != b.num_data[i]) {
      return false;
    }
  }
  return true;
}

bool BigInt::operator!=(const BigInt &b) const {
  if (sign != b.sign) {
    return true;
  }
  if (num_len != b.num_len) {
    return true;
  }
  int i;
  for (i = 0; i < num_len; i++) {
    if (num_data[i] != b.num_data[i]) {
      return true;
    }
  }
  return false;
}

bool BigInt::operator>(const BigInt &b) const {
  if (*this == b) return false;
  if (sign == true && b.sign == false) {
    return true;
  }
  if (sign == false && b.sign == true) {
    return false;
  }
  if (sign == true && b.sign == true && (num_len > b.num_len)) {
    return true;
  } else if (sign == true && b.sign == true && (num_len < b.num_len)) {
    return false;
  } else if (sign == false && b.sign == false && (num_len > b.num_len)) {
    return false;
  } else if (sign == false && b.sign == false && (num_len < b.num_len)) {
    return true;
  }
  int i;
  bool temp;
  for (i = num_len - 1; i > 0; i--) {
    if (num_data[i] > b.num_data[i]) {
      temp = true;
      break;
    } else if (num_data[i] < b.num_data[i]) {
      temp = false;
      break;
    }
  }
  if (sign == true) {
    return temp;
  } else {
    return (!temp);
  }
}

bool BigInt::operator<(const BigInt &b) const {
  int temp = (*this == b);
  if (temp) {
    return false;
  }
  return (!(*this > b));
}

bool BigInt::operator>=(const BigInt &b) const {
  return ((*this == b) || (*this > b));
}
bool BigInt::operator<=(const BigInt &b) const {
  return ((*this == b) || (*this < b));
}

BigInt::BigInt(const BigInt &b) {
  int i;
  if (this != &b) {
    num_len = b.num_len;
    sign = b.sign;
    if (num_data != b.num_data) {
      int *temp_num = new int[b.num_len];
      for (i = 0; i < num_len; i++) {
        temp_num[i] = b.num_data[i];
      }
      delete[] num_data;
      num_data = temp_num;
    }
  }
}

BigInt &BigInt::operator=(const BigInt &b) {
  int i;
  if (this == &b) {
    return *this;
  }
  num_len = b.num_len;
  sign = b.sign;
  int *temp_num = new int[num_len];
  delete[] num_data;
  for (i = 0; i < num_len; i++) {
    temp_num[i] = b.num_data[i];
  }
  num_data = temp_num;
  return *this;
}

BigInt BigInt::summar(const BigInt &a, const BigInt &b) const {
  int final_len;
  int min_len;
  int max_len;
  int i;
  final_len = a.num_len + 1;
  max_len = a.num_len;
  min_len = b.num_len;
  int *temp_data = new int[final_len];
  for (i = 0; i < final_len; i++) {
    temp_data[i] = 0;
  }
  int hold = 0;
  for (i = 0; i < min_len; i++) {
    temp_data[i] = (hold + a.num_data[i] + b.num_data[i]) % 1000;
    hold = (hold + a.num_data[i] + b.num_data[i]) / 1000;
  }
  for (i = min_len; i < final_len - 1; i++) {
    temp_data[i] = (hold + a.num_data[i]) % 1000;
    hold = (hold + a.num_data[i]) / 1000;
  }
  temp_data[final_len - 1] = hold;
  if (temp_data[final_len - 1] != 0) {
    BigInt res(final_len, 0);
    for (i = 0; i < final_len; i++) {
      res.num_data[i] = temp_data[i];
    }
    delete[] temp_data;
    return res;
  } else {
    BigInt res(final_len - 1, 0);
    for (i = 0; i < final_len - 1; i++) {
      res.num_data[i] = temp_data[i];
    }
    delete[] temp_data;
    return res;
  }
}

BigInt BigInt::differ(const BigInt &a, const BigInt &b) const {
  int len_temp = a.num_len;
  int min_len = b.num_len;
  int i;
  int *temp_data = new int[len_temp];
  for (i = 0; i < len_temp; i++) {
    temp_data[i] = 0;
  }
  for (i = 0; i < min_len; i++) {
    temp_data[i] = a.num_data[i] - b.num_data[i] + temp_data[i];
    if (temp_data[i] < 0) {
      temp_data[i + 1] = temp_data[i + 1] - 1;
      temp_data[i] = temp_data[i] + 1000;
    }
  }
  for (i = min_len; i < len_temp; i++) {
    temp_data[i] = temp_data[i] + a.num_data[i];
  }
  for (i = min_len; i < len_temp; i++) {
    if (temp_data[i] < 0) {
      temp_data[i] = temp_data[i] + 1000;
      temp_data[i + 1]--;
    }
  }
  int helper = len_temp;
  for (i = helper - 1; i > 0; i--) {
    if (temp_data[i] == 0) {
      len_temp--;
    } else {
      break;
    }
  }
  BigInt res(len_temp, 0);
  for (i = 0; i < len_temp; i++) {
    res.num_data[i] = temp_data[i];
  }
  res.num_data[len_temp - 1] = abs(res.num_data[len_temp - 1]);
  delete[] temp_data;
  return res;
}

BigInt::~BigInt() {
  if (num_data != nullptr) delete[] num_data;
  num_len = 0;
  sign = true;
}

BigInt BigInt::mult(const BigInt &a, const BigInt &b) const {
  int temp_len = a.num_len * 2 + 1;
  int i;
  int j;
  int *temp_data = new int[temp_len];
  for (i = 0; i < temp_len; i++) {
    temp_data[i] = 0;
  }
  int min_len = b.num_len;
  int max_len = a.num_len;
  int hold;

  for (i = 0; i < min_len; i++) {
    hold = 0;
    for (j = 0; j < max_len; j++) {
      temp_data[i + j] =
          temp_data[i + j] + b.num_data[i] * a.num_data[j] + hold;
      hold = temp_data[i + j] / 1000;
      temp_data[i + j] = temp_data[i + j] % 1000;
      if (j == (max_len - 1)) {
        temp_data[i + j + 1] += hold;
      }
    }
  }
  int len_to_put = 0;
  for (i = temp_len - 1; i >= 0; i--) {
    if (temp_data[i] != 0) {
      len_to_put = i + 1;
      break;
    }
  }
  if (len_to_put == 0) {
    len_to_put++;
  }
  BigInt res(len_to_put, 0);
  for (i = 0; i < len_to_put; i++) {
    res.num_data[i] = temp_data[i];
  }
  delete[] temp_data;
  return res;
}

BigInt BigInt::operator-() {
  std::stringstream a;
  a<<*this;
  BigInt res(a.str());
  res.sign = (!sign);
  return res;
}

BigInt BigInt::operator+(const BigInt &b) const {
  if (num_len >= b.num_len) {
    if (sign == true && b.sign == true)
      return summar(*this, b);
    else if (sign == false && b.sign == false)
      return -summar(*this, b);
    else if (sign == true && b.sign == false)
      return differ(*this, b);
    else if (sign == false && b.sign == true)
      return -differ(*this, b);
  } else {
    if (sign == true && b.sign == true)
      return summar(b, *this);
    else if (sign == false && b.sign == false)
      return -summar(b, *this);
    else if (sign == true && b.sign == false)
      return differ(b, *this);
    else if (sign == false && b.sign == true)
      return -differ(b, *this);
  }
  BigInt res;
  return res;
}

BigInt BigInt::operator-(const BigInt &b) const {
  if (num_len >= b.num_len) {
    if (sign == true && b.sign == true) {
      return differ(*this, b);
    } else if (sign == false && b.sign == false)
      return -summar(*this, b);
    else if (sign == true && b.sign == false)
      return summar(*this, b);
    else if (sign == false && b.sign == true)
      return -summar(*this, b);
  } else {
    if (sign == true && b.sign == true)
      return -differ(b, *this);
    else if (sign == false && b.sign == false)
      return -summar(b, *this);
    else if (sign == true && b.sign == false)
      return summar(b, *this);
    else if (sign == false && b.sign == true)
      return -summar(b, *this);
  }
  BigInt res;
  return res;
}

BigInt BigInt::operator*(const BigInt &b) const {
  if (num_len >= b.num_len) {
    if (sign == b.sign) {
      return mult(*this, b);
    } else {
      return -mult(*this, b);
    }
  } else {
    if (sign == b.sign) {
      return mult(b, *this);
    } else {
      return -mult(b, *this);
    }
  }
}

BigInt BigInt::operator+(const int &b) const {
  int z = b;
  BigInt bb(z);
  BigInt res = (*this) + bb;
  return res;
}

BigInt BigInt::operator-(const int &b) const {
  int z = b;
  BigInt bb(z);
  BigInt res = (*this) - bb;
  return res;
}

BigInt BigInt::operator*(const int &b) const {
  int z = b;
  BigInt bb(z);
  BigInt res = (*this) * bb;
  return res;
}

std::ostream &operator<<(std::ostream &cc, BigInt &b) {
  int i;
  if (b.sign == false) {
    cc << "-";
  }
  for (i = b.num_len - 1; i >= 0; i--) {
    if (b.num_data[i] == 0 && i != b.num_len - 1) {
      cc << "000";
    } else if (b.num_data[i] / 10 == 0 && i != b.num_len - 1) {
      cc << "00" << b.num_data[i];
    } else if (b.num_data[i] / 100 == 0 && i != b.num_len - 1) {
      cc << "0" << b.num_data[i];
    } else {
      cc << b.num_data[i];
    }
  }
  return cc;
}

BigInt::BigInt(BigInt &&other)
    : num_data(other.num_data), sign(other.sign), num_len(other.num_len) {
  other.num_data = nullptr;
  other.sign = true;
  other.num_len = 0;
}

BigInt &BigInt::operator=(BigInt &&other) {
  if (this == &other) {
    return *this;
  }
  delete[] num_data;
  num_data = other.num_data;
  sign = other.sign;
  num_len = other.num_len;
  other.num_data = nullptr;
  other.sign = true;
  other.num_len = 0;
  return *this;
}

int BigInt::get_length() const { return num_len; }

bool BigInt::is_null_ptr() const { return (num_data == nullptr); }
