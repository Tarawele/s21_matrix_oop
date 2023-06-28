#include "s21_matrix_oop.hpp"
#include <gtest/gtest.h>

using namespace std;

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(NULL) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  this->mem_alloc();
}

S21Matrix::~S21Matrix() { this->destroy_matrix(); }

void S21Matrix::destroy_matrix() {
  if (this->matrix_ != nullptr) {
    for (int i = 0; i < this->rows_; ++i) {
      delete this->matrix_[i];
    }
    delete this->matrix_;
  }
  this->matrix_ = nullptr;
  this->cols_ = 0;
  this->rows_ = 0;
}

void S21Matrix::mem_alloc() {
  if ((this->cols_ <= 0) + (this->rows_ <= 0)) {
    throw out_of_range("Error: out of range");
  }
  this->matrix_ = new double *[this->rows_];
  for (int i = 0; i < this->rows_; ++i) {
    this->matrix_[i] = new double[this->cols_];
  }
}

void S21Matrix::copy_matrix(const S21Matrix &other) {
  if ((this->rows_ != other.rows_) + (cols_ != other.cols_)) {
    throw out_of_range("Error: Matrix have different dimensions");
  }
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::set_rows(int rows) {
  S21Matrix tmp(*this);
  this->destroy_matrix();
  rows_ = rows;
  cols_ = tmp.cols_;
  this->mem_alloc();
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] = tmp.matrix_[i][j];
    }
  }
}

void S21Matrix::set_cols(int cols) {
  S21Matrix tmp(*this);
  this->destroy_matrix();
  cols_ = cols;
  rows_ = tmp.rows_;
  this->mem_alloc();
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] = tmp.matrix_[i][j];
    }
  }
}

int S21Matrix::get_cols() { return this->cols_; }
int S21Matrix::get_rows() { return this->rows_; }

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_) {
  this->copy_matrix(other);
  other.destroy_matrix();
}
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  this->mem_alloc();
  this->copy_matrix(other);
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if ((this->rows_ != other.rows_) + (this->cols_ != other.cols_)) {
    throw out_of_range("Error: Matrix have different dimensions");
  }
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if ((this->rows_ != other.rows_) + (this->cols_ != other.cols_)) {
    throw out_of_range("Error: Matrix have different dimensions");
  }
  for (int i = 0; i < other.rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (other.cols_ == this->cols_ && other.rows_ == this->rows_) {
    for (int i = 0; i < other.rows_ && result; ++i) {
      for (int j = 0; j < other.cols_ && result; ++j) {
        if (fabs(other.matrix_[i][j] - this->matrix_[i][j]) >= 1e-7) {
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
    throw out_of_range("Error: the number of columns of the first matrix is "
                       "not equal to the number of rows of the second matrix");
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
    throw out_of_range("Error: Determinant = 0");
  }
  S21Matrix neo(this->rows_, this->cols_);
  S21Matrix temp = this->CalcComplements();
  S21Matrix second_temp = temp.Transpose();
  neo = second_temp;
  neo.MulNumber(1 / det);

  return neo;
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->rows_ != this->cols_) {
    throw out_of_range("Error: Matrix have different dimensions");
  }
  S21Matrix neo(this->rows_, this->cols_);
  if (this->rows_ == 1 && this->cols_ == 1) {
    neo.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < neo.rows_; ++i) {
      for (int j = 0; j < neo.cols_; ++j) {
        S21Matrix temp = MinorMatrix(*this, i, j);
        neo.matrix_[i][j] = temp.Determinant() * pow(-1.0, (i + 1) + (j + 1));
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
    throw out_of_range("Error: Matrix have different dimensions");
  }
  double det = 0;
  if (this->rows_ == 1 && this->cols_ == 1) {
    det = matrix_[0][0];
  } else if (this->rows_ == 2 && this->cols_ == 2) {
    det = (this->matrix_[0][0] * this->matrix_[1][1]) -
          (this->matrix_[1][0] * this->matrix_[0][1]);
  } else {
    for (int i = 1; i <= this->cols_; ++i) {
      S21Matrix neo = MinorMatrix(*this, 0, i - 1);
      det += pow(-1, 1 + (double)i) * matrix_[0][i - 1] * neo.Determinant();
    }
  }
  return det;
}
S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}
S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}
S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix tmp(*this);
  tmp.MulNumber(num);

  return tmp;
}
bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
};

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}
S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  this->destroy_matrix();
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->mem_alloc();
  this->copy_matrix(other);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if ((row >= this->rows_) + (col >= this->cols_) + (row < 0) + (col < 0)) {
    throw out_of_range("Error: out of range");
  }
  return this->matrix_[row][col];
}

S21Matrix operator*(const double num, const S21Matrix &other) {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}