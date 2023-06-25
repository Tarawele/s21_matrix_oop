#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::~S21Matrix() {this->destroy_matrix();}

void S21Matrix::destroy_matrix() {
    if (this->matrix_ != nullptr) {
        for (int i = 0; i < this->rows_; ++i) {
            delete[] this->matrix_[i];
        }
        delete[] matrix_;
    }
    this->matrix_ = nullptr;
    this->cols_ = 0;
    this->rows_ = 0;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows <= 0 || cols <= 0) {
        throw out_of_range("Error: out of range");
    }
    this->mem_alloc();
}

void S21Matrix::mem_alloc() {
    if (rows_ <=  0 || cols_ <= 0) {
        throw out_of_range("Error: out of range");
    }
    this->matrix_ = new double*[this->rows_]();
    for (int i = 0; i < this->rows_; ++i)
    {
        this->matrix_[i] = new double[this->cols_]();
    }
}

void S21Matrix::copy_matrix(const S21Matrix& other) {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
        throw out_of_range("Error: different matrix dimensions");
    } else {
        this->matrix_ = new double*[this->rows_]();
        for (int i = 0; i < this->rows_; ++i) {
            for (int j = 0; j < this->cols_; ++j) {
                this->matrix_[i][j] = other.matrix_[i][j];
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
    for (int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->cols_; j++)
        {
            this->matrix_[i][j] =  tmp.matrix_[i][j];
        }
    }
}

void S21Matrix::set_cols(int cols) {
    S21Matrix tmp(*this);
    this->destroy_matrix();
    cols_ = cols;
    rows_ = tmp.rows_;
    this->mem_alloc();
    for (int i = 0; i < this->rows_; i++) {
        for (int  j = 0; j < this->cols_; j++) {
            this->matrix_[i][j] = tmp.matrix_[i][j];
        }
    }
}

int S21Matrix::get_cols() {return this->cols_; }
int S21Matrix::get_rows() {return this->rows_; }

S21Matrix::S21Matrix(const S21Matrix& other) : rows_(other.rows_), cols_(other.cols_){
    this->mem_alloc();
    this->copy_matrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) : rows_(other.rows_), cols_(other.cols_) {
    this->copy_matrix(other);
    other.destroy_matrix();
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
        throw out_of_range("Error: matrix have different dimensions");
    } else {
        for (int  i = 0; i < other.rows_; i++) {
            for (int  j = 0; j < other.cols_; j++) {
                this->matrix_[i][j] += other.matrix_[i][j];
            }   
        }   
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw out_of_range("Error: matrix have different dimensions");
    } else {
        for (int i = 0; i < other.rows_; i++) {
            for (int j = 0; j < other.cols_; j++) {
                this->matrix_[i][j] -= other.matrix_[i][j];
            }
        }
    }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
    S21Matrix M(*this);
    M.SumMatrix(other);
    return M; 
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
    S21Matrix M(*this);
    M.SubMatrix(other);
    return M;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
    SumMatrix(other);
    return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
    SubMatrix(other);
    return *this;
}

double& S21Matrix::operator()(int row, int col) {
    if (row >= this->rows_ || col >= this->cols_ || row < 0 || col < 0) {
        throw std::out_of_range("Error: out of range");
    }
    return this->matrix_[row][col];
}

bool S21Matrix::operator==(const S21Matrix& other) { return this->eq_matrix(other); }

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    this->destroy_matrix();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->mem_alloc();
    this->copy_matrix(other);
    return *this;
}

bool S21Matrix::eq_matrix(const S21Matrix& other) {
    bool res = true;
    if (other.cols_ == this->cols_ && other.rows_ == this->rows_) {
        for (int i = 0; i < other.rows_ && res; ++i) {
            for (int j = 0; j < other.cols_ && res; ++j) {
                if (fabs(other.matrix_[i][j] - this->matrix_[i][j]) >= E) {
                    res = false;
                }
            }
        }
    } else {
        res = false;
    }
    return res;
}