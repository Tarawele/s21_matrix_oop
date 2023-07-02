#include "s21_matrix_oop.h"

S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows <= 0 && cols <= 0) {
    throw std::out_of_range("Error: rows and cols are incorrect");
  }
  mem_alloc();
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      matrix_[i][j] = 0.0;
    }
  }
}

S21Matrix::~S21Matrix() { destroy_matrix(); }

void S21Matrix::destroy_matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}
void S21Matrix::mem_alloc() {
  if ((cols_ <= 0) || (rows_ <= 0)) {
    throw std::out_of_range("Error: out of range");
  }
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }
}

void S21Matrix::copy_matrix(const S21Matrix &other) {
  if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
    throw std::out_of_range("Error: Matrix have different dimensions");
  }
  if (matrix_ != other.matrix_) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
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

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  mem_alloc();
  copy_matrix(other);
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
S21Matrix operator*(const double num, const S21Matrix &other) {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}
bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); };

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
  if (this != &other) {
    destroy_matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    mem_alloc();
    copy_matrix(other);
  }
  return *this;
}
S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}
double &S21Matrix::operator()(int row, int col) const {
  if ((row > rows_) && (col > cols_) && (row < 0) && (col < 0)) {
    throw std::out_of_range("Error: out of range");
  }
  return matrix_[row][col];
}