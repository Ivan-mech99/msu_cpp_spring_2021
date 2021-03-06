#include <iostream>
#include <cassert>
#include "my_matrix.h"
using std::cout;
using std::endl;

void Number_of_rows_and_cols() {
  Matrix mat(10, 12);
  int ans1 = 10;
  int ans2 = 12;
  int res1 = mat.Rows_amount();
  int res2 = mat.Cols_amount();
  assert((ans1 == res1) && (ans2 == res2));
}

void Get_required_element() {
  Matrix mat(3, 3);
  int i;
  int j;
  int num = 1;
  int ans;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      mat[i][j] = num;
      num = num + 1;
    }
  }
  ans = mat[1][2];
  assert(ans == 6);
}

void Multiplication_test() {
  Matrix mat1(3, 3);
  Matrix mat2(3, 3);
  int i;
  int j;
  int num = 1;
  bool ans = true;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      mat1[i][j] = num;
      mat2[i][j] = num * 3;
      num = num + 1;
    }
  }
  mat1 *= 3;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (mat1[i][j] != mat2[i][j]) {
        ans = false;
      }
    }
  }
  assert(ans);
}

void Ostream_matrix_test() {
  Matrix mat1(5, 5);
  int i;
  int j;
  int num = 1;
  bool ans = true;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      mat1[i][j] = num;
      num = num + 1;
    }
  }
  cout << mat1;
}

void Sum_of_correctly_shaped_matrices() {
  Matrix A(5, 5);
  Matrix B(5, 5);
  Matrix C(5, 5);
  Matrix D(5, 5);
  int i;
  int j;
  int num1 = 1;
  int num2 = 10;
  bool ans = true;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      B[i][j] = num1;
      C[i][j] = num2;
      D[i][j] = num1 + num2;
      num1 = num1 + 1;
      num2 = num2 + 10;
    }
  }
  A = B + C;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (A[i][j] != D[i][j]) {
        ans = false;
      }
    }
  }
  assert(ans);
}

void Sum_of_incorrectly_shaped_matrices() {
  Matrix A(5, 5);
  Matrix B(5, 6);
  Matrix C(6, 5);
  int i;
  int j;
  bool ans = false;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 6; j++) {
      B[i][j] = i + j;
    }
  }
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 5; j++) {
      C[i][j] = i + j;
    }
  }
  try {
    A = B + C;
  } catch (const std::out_of_range& ex) {
    cout << ex.what();
    ans = true;
  }
  assert(ans);
}

void Equality_comparison_test() {
  Matrix mat1(3, 3);
  Matrix mat2(3, 3);
  int i;
  int j;
  int num = 1;
  bool ans1;
  bool ans2;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      mat1[i][j] = num;
      mat2[i][j] = num;
      num = num + 1;
    }
  }
  ans1 = (mat1 == mat2);
  mat2[0][0] = -9999;
  ans2 = (mat1 == mat2);
  assert(ans1 && (!ans2));
}

void Inequality_comparison_test() {
  Matrix mat1(3, 3);
  Matrix mat2(3, 3);
  int i;
  int j;
  int num = 1;
  bool ans1;
  bool ans2;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      mat1[i][j] = num;
      mat2[i][j] = num;
      num = num + 1;
    }
  }
  ans1 = (mat1 != mat2);
  mat2[0][0] = -9999;
  ans2 = (mat1 != mat2);
  assert((!ans1) && ans2);
}

void Out_of_range_elem_test() {
  Matrix C(3, 3);
  int i;
  int j;
  bool ans1 = false;
  bool ans2 = false;
  bool ans3 = false;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      C[i][j] = 0;
    }
  }
  try {
    C[0][-1] = 100;
  } catch (const std::out_of_range& ex) {
    cout << ex.what();
    ans1 = true;
  }
  try {
    C[500][0] = 100;
  } catch (const std::out_of_range& ex) {
    cout << ex.what();
    ans2 = true;
  }
  try {
    C[0][500] = 100;
  } catch (const std::out_of_range& ex) {
    cout << ex.what();
    ans3 = true;
  }
  assert(ans1 && ans2 && ans3);
}

void Matrix_Sum_test() {
  Matrix A(5, 5);
  Matrix B(5, 5);
  Matrix C(5, 5);
  Matrix D(5, 5);
  int i;
  int j;
  int num1 = 1;
  int num2 = 10;
  bool ans = true;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      B[i][j] = num1;
      C[i][j] = num2;
      D[i][j] = num1 + num2;
      num1 = num1 + 1;
      num2 = num2 + 10;
    }
  }
  cout << "Sum test: " << endl;
  cout << "Matrix B: " << endl;
  cout << B;
  cout << "Matrix C: " << endl;
  cout << C;
  A = B + C;
  cout << "Result of B + C: " << endl;
  cout << A;
  assert(A == D);
}

void Matrix_Assignment_test() {
  cout << "Assingment test" << endl;
  Matrix B(3, 3);
  int i, j;
  int ind = 1;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      B[i][j] = ind;
      ind++;
    }
  }
  Matrix C(2, 2);
  C[0][0] = 98;
  C[0][1] = 99;
  C[1][0] = 100;
  C[1][1] = 101;
  cout << "Matrix B:" << endl;
  cout << B;
  cout << "Matrix C:" << endl;
  cout << C;
  cout << "C after C = B:" << endl;
  C = B;
  cout << C;
  Matrix D = B;
  cout << "D (uninitialized) = B:" << endl;
  cout << D;
  assert(D == B && C == B);
}

void Matrix_1x1_test() {
  Matrix A(1, 1);
  A[0][0] = 589;
  bool ans1 = (A[0][0] == 589);
  bool ans2 = ((A.Rows_amount() == 1) && (A.Cols_amount() == 1));
  A *= 2;
  bool ans3 = (A[0][0] = 589 * 2);
  Matrix B(1, 1);
  B[0][0] = 643;
  A = A + B;
  bool ans4 = (A[0][0] = 589 * 2 + 643);
  assert(ans1 && ans2 && ans3 && ans4);
}

int main() {
  Number_of_rows_and_cols();
  Get_required_element();
  Multiplication_test();
  Ostream_matrix_test();
  Sum_of_correctly_shaped_matrices();
  Sum_of_incorrectly_shaped_matrices();
  Equality_comparison_test();
  Inequality_comparison_test();
  Out_of_range_elem_test();
  Matrix_Assignment_test();
  Matrix_Sum_test();
  Matrix_1x1_test();
  cout << "Success!" << endl;
  getchar();
  return 0;
}
