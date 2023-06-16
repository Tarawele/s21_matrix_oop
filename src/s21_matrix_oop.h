#ifndef S21_MATRIX_OPP_H_
#define S21_MATRIX_OPP_H_

#include <iostream>
#include <cmath>
#define E 1e-7
using namespace std;

class S21Matrix {
    public:
        S21Matrix();              // Default constructor
        ~S21Matrix();             // Destructor
        S21Matrix(int rows, int cols);
        S21Matrix(S21Matrix&& other);
        S21Matrix(const S21Matrix& other);

        //Basics' operations
        void SumMatrix(const S21Matrix& other); 
        void SubMatrix(const S21Matrix& other);
        bool eq_matrix(const S21Matrix& other);

        double& operator()(int row, int col);
        bool operator==(const S21Matrix& other);
        S21Matrix& operator=(const S21Matrix& other);

        //Operators
        S21Matrix operator+(const S21Matrix& other);
        S21Matrix operator-(const S21Matrix& other);

        //Assignement operators
        S21Matrix& operator+=(const S21Matrix& other);
        S21Matrix& operator-=(const S21Matrix& other);

        //getters and setters
        void set_rows(int rows);
        void set_cols(int cols);
        int get_rows();
        int get_cols();

        // Other methods..
    private:
        // Attributes
        int rows_, cols_;         // Rows and columns
        double **matrix_;         // Pointer to the memory where the matrix is allocated
        void mem_alloc();
        void destroy_matrix();
        void copy_matrix(const S21Matrix& other);
};

#endif // S21_MATRIX_OOP_H_