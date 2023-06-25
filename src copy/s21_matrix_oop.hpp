#ifndef S21_MATRIX_OOP_HPP
#define S21_MATRIX_OOP_HPP

#include <cmath>
#include <iostream>

class S21Matrix {
private:
  // Attributes
  int rows_, cols_; // Rows and columns
  double **matrix_; // Pointer to the memory where the matrix is allocated
  void mem_alloc();
  void destroy_matrix();
  void copy_matrix(const S21Matrix &other);

public:
  S21Matrix();  // Default constructor
  ~S21Matrix(); // Destructor
  S21Matrix(int rows, int cols);
  S21Matrix(S21Matrix &&other);
  S21Matrix(const S21Matrix &other);

  // Basics' operations
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  bool EqMatrix(const S21Matrix &other);

  // Overloads Operators
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);

  // Assignement operators
  bool operator==(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);

  // getters and setters
  void set_rows(int rows);
  void set_cols(int cols);
  int get_rows();
  int get_cols();
  // Other methods..
  double &operator()(int row, int col);
};

#endif // S21_MATRIX_OOP_HPP