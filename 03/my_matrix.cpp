#include <iostream>
#include <iomanip>
#include "my_matrix.h"

Matrix::ProxyRow::ProxyRow(int* mat_row, int num_col1) {
  data_ = mat_row;
  needed_col_num = num_col1;
}

int& Matrix::ProxyRow::operator[](int wanted_col_num) {
  if (wanted_col_num >= needed_col_num || wanted_col_num < 0) {
    throw std::out_of_range("");
  }
  return data_[wanted_col_num];
}

Matrix::Matrix(int rows, int cols) {
  int i;
  mdata = new int*[rows];
  for (i = 0; i < rows; ++i) {
    mdata[i] = new int[cols];
  }
  num_rows = rows;
  num_cols = cols;
}

Matrix::~Matrix() {
  int i;
  for (i = 0; i < num_rows; i++) {
    delete[] mdata[i];
  }
  delete[] mdata;
}

Matrix::Matrix(const Matrix& obj) {
  int i;
  int j;
  num_rows = obj.num_rows;
  num_cols = obj.num_cols;
  mdata = new int*[num_rows];
  for (i = 0; i < num_rows; i++) {
    mdata[i] = new int[num_cols];
  }
  for (i = 0; i < num_rows; i++) {
    for (j = 0; j < num_cols; j++) {
      mdata[i][j] = obj.mdata[i][j];
    }
  }
}

int Matrix::Rows_amount() const { return num_rows; }

int Matrix::Cols_amount() const { return num_cols; }

Matrix Matrix::operator+(const Matrix& mat2) const {
  int i;
  int j;
  if (num_rows != mat2.num_rows || num_cols != mat2.num_cols) {
    throw std::out_of_range("");
  }
  Matrix result(num_rows, num_cols);
  for (i = 0; i < num_rows; i++) {
    for (j = 0; j < num_cols; j++) {
      result.mdata[i][j] = mdata[i][j] + mat2.mdata[i][j];
    }
  }
  return result;
}

Matrix& Matrix::operator=(const Matrix& mat2) {
  int i;
  int j;
  for (i = 0; i < num_rows; i++) {
    if (mdata[i] != nullptr) {
      delete[] mdata[i];
    }
  }
  if (mdata != nullptr) {
    delete[] mdata;
  }
  num_rows = mat2.num_rows;
  num_cols = mat2.num_cols;
  mdata = new int*[num_rows];
  for (i = 0; i < num_rows; i++) {
    mdata[i] = new int[num_cols];
  }
  for (i = 0; i < num_rows; i++) {
    for (j = 0; j < num_cols; j++) {
      mdata[i][j] = mat2.mdata[i][j];
    }
  }
  return *this;
}

Matrix& Matrix::operator*=(int coeff) {
  int i;
  int j;
  for (i = 0; i < num_rows; i++) {
    for (j = 0; j < num_cols; j++) {
      mdata[i][j] = mdata[i][j] * coeff;
    }
  }
  return *this;
}

bool Matrix::operator==(const Matrix& mat2) const {
    int i;
    int j;
    if ((num_rows != mat2.num_rows) || (num_cols != mat2.num_cols)) {
      return false;
    } else {
      for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
          if (mdata[i][j] != mat2.mdata[i][j]) return false;
        }
      }
    }
    return true;
  }

bool Matrix::operator!=(const Matrix& mat2) const {
    int i, j;
    if ((num_rows != mat2.num_rows) || (num_cols != mat2.num_cols)) {
      return true;
    } else {
      for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
          if (mdata[i][j] != mat2.mdata[i][j]) return true;
        }
      }
    }
    return false;
  }

Matrix::ProxyRow Matrix::operator[](int needed_row_num) {
  if (needed_row_num >= num_rows || needed_row_num < 0) {
    throw std::out_of_range("");
  }
  return ProxyRow(mdata[needed_row_num], num_cols);
}

std::ostream& operator<<(std::ostream& cc, Matrix& mat) {
  cc << '\n';
  int i;
  int j;
  for (i = 0; i < mat.num_rows; i++) {
    for (j = 0; j < mat.num_cols; j++) {
      cc << std::setw(8) << mat[i][j] << ' ';
    }
    cc << '\n';
  }
  cc << '\n';
  return cc;
}
