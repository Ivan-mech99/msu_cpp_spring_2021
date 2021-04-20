#ifndef H_MY_MATRIX
#define H_MY_MATRIX
class Matrix {
  int num_rows;
  int num_cols;
  class ProxyRow {
    int* data_;
    int needed_col_num;

   public:
    ProxyRow(int* mat_row, int num_col1);
    int& operator[](int wanted_col_num);
  };
  int** mdata;

 public:
  Matrix(int rows, int cols);
  ~Matrix();
  Matrix(const Matrix& obj);
  int Rows_amount() const;
  int Cols_amount() const;
  Matrix operator+(const Matrix& mat2) const;
  Matrix& operator=(const Matrix& mat2);
  Matrix& operator*=(int coeff);
  bool operator==(const Matrix& mat2) const;
  bool operator!=(const Matrix& mat2) const;
  friend std::ostream& operator<<(std::ostream& cc, Matrix& mat);
  ProxyRow operator[](int needed_row_num);
};

#endif
