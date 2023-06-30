#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  // Method
  // S21Matrix();  // Default constructor
  S21Matrix(int rows = 0, int cols = 0);
  S21Matrix(S21Matrix &&other) noexcept;
  S21Matrix(const S21Matrix &other);
  ~S21Matrix();  // Destructor

  // Operations
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  bool EqMatrix(const S21Matrix &other) const noexcept;
  void MulMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  //  Operators
  friend S21Matrix operator*(const double num, const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double num);

  // getters, setters and helpers
  void set_rows(int rows);
  void set_cols(int cols);
  int get_rows();
  int get_cols();
  S21Matrix MinorMatrix(const S21Matrix &other, int m_rows, int m_cols);
  double &operator()(int row, int col) const;
  void mem_alloc();
  void destroy_matrix();
  void copy_matrix(const S21Matrix &other);

 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double **matrix_;  // Pointer to the memory where the matrix is allocated
};
#endif  // S21_MATRIX_OOP_HPP