#include "s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    throw std::out_of_range("Error: Matrix have different dimensions");
  }
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    throw std::out_of_range("Error: Matrix have different dimensions");
  }
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool result = true;
  if (other.cols_ == cols_ && other.rows_ == rows_) {
    for (int i = 0; i < other.rows_ && result; ++i) {
      for (int j = 0; j < other.cols_ && result; ++j) {
        if (fabs(other.matrix_[i][j] - matrix_[i][j]) >= 1e-7) {
          result = false;
        }
      }
    }
  } else {
    result = false;
  }
  return result;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range("Error: rows_ and cols_ of matrixes are different");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < rows_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0 || rows_ != cols_) {
    throw std::out_of_range("Error: Determinant = 0");
  }
  S21Matrix neo(rows_, cols_);
  S21Matrix temp = CalcComplements();
  S21Matrix second_temp = temp.Transpose();
  neo = second_temp;
  neo.MulNumber(1.0 / det);

  return neo;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::out_of_range("Error: Matrix have different dimensions");
  }
  S21Matrix neo(rows_, cols_);
  if (rows_ == 1 && cols_ == 1) {
    neo.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < neo.rows_; ++i) {
      for (int j = 0; j < neo.cols_; ++j) {
        S21Matrix temp = MinorMatrix(*this, i, j);
        neo.matrix_[i][j] = temp.Determinant() * pow(-1.0, (i + j));
      }
    }
  }
  return neo;
}

S21Matrix S21Matrix::MinorMatrix(const S21Matrix &other, int i_rows,
                                 int j_cols) {
  S21Matrix neo(other.rows_ - 1, other.cols_ - 1);
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      if (i != i_rows && j != j_cols) {
        if (i > i_rows && j < j_cols) {
          neo.matrix_[i - 1][j] = other.matrix_[i][j];
        } else if (i > i_rows && j > j_cols) {
          neo.matrix_[i - 1][j - 1] = other.matrix_[i][j];
        } else if (i < i_rows && j > j_cols) {
          neo.matrix_[i][j - 1] = other.matrix_[i][j];
        } else {
          neo.matrix_[i][j] = other.matrix_[i][j];
        }
      }
    }
  }

  return neo;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::out_of_range("Error: Matrix have different dimensions");
  }
  double det = 0.0;
  if (rows_ == 1 && cols_ == 1) {
    det = matrix_[0][0];
  } else if (rows_ == 2 && cols_ == 2) {
    det = (matrix_[0][0] * matrix_[1][1]) - (matrix_[1][0] * matrix_[0][1]);
  } else {
    for (int j = 1; j <= cols_; ++j) {
      S21Matrix neo = MinorMatrix(*this, 0, j - 1);
      det += pow(-1, 1 + (double)j) * matrix_[0][j - 1] * neo.Determinant();
    }
  }
  return det;
}