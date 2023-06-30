#include "s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if ((this->rows_ != other.rows_) + (this->cols_ != other.cols_)) {
    throw std::out_of_range("Error: Matrix have different dimensions");
  }
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if ((this->rows_ != other.rows_) + (this->cols_ != other.cols_)) {
    throw std::out_of_range("Error: Matrix have different dimensions");
  }
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const noexcept {
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
  if (this->cols_ != other.rows_) {
    throw std::out_of_range("Error: rows_ and cols_ of matrixes are different");
  }
  S21Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < this->rows_; ++k) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] *= num;
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix result(this->cols_, this->rows_);
  for (int i = 0; i < result.rows_; ++i) {
    for (int j = 0; j < result.cols_; ++j) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0 || this->rows_ != cols_) {
    throw std::out_of_range("Error: Determinant = 0");
  }
  S21Matrix neo(this->rows_, this->cols_);
  S21Matrix temp = this->CalcComplements();
  S21Matrix second_temp = temp.Transpose();
  neo = second_temp;
  neo.MulNumber(1.0 / det);

  return neo;
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->rows_ != this->cols_) {
    throw std::out_of_range("Error: Matrix have different dimensions");
  }
  S21Matrix neo(this->rows_, this->cols_);
  if (this->rows_ == 1 && this->cols_ == 1) {
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
  if (this->rows_ != this->cols_) {
    throw std::out_of_range("Error: Matrix have different dimensions");
  }
  double det = 0;
  if (this->rows_ == 1 && this->cols_ == 1) {
    det = matrix_[0][0];
  } else if (this->rows_ == 2 && this->cols_ == 2) {
    det = (this->matrix_[0][0] * this->matrix_[1][1]) -
          (this->matrix_[1][0] * this->matrix_[0][1]);
  } else {
    for (int j = 1; j <= this->cols_; ++j) {
      S21Matrix neo = MinorMatrix(*this, 0, j - 1);
      det += pow(-1, 1 + (double)j) * matrix_[0][j - 1] * neo.Determinant();
    }
  }
  return det;
}