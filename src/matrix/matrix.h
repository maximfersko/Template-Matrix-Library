#ifndef MATRIX_H_
#define MATRIX_H_

#include <cmath>
#include <fstream>
#include <iostream>

template <class T>
class Matrix {
    friend Matrix operator*(const Matrix& other, const double num);
    friend Matrix operator*(const double num, const Matrix& other);

   public:
    //  Constructor & Destructor

    Matrix();
    Matrix(int rows, int columns);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    explicit Matrix(const std::string filename);
    explicit Matrix(std::initializer_list<T> const& items);
    ~Matrix();

    //  Methods

    int getRows() const;
    int getColumn() const;
    void setRows(int rows);
    void setColumn(int columns);
    bool matrix_eq(const Matrix& other);
    void matrix_sum(const Matrix& other);
    void matrix_sub(const Matrix& other);
    void mul_number(const double num);
    void matrix_mul(const Matrix& other);
    Matrix transpose();
    Matrix calc_complements();
    Matrix inversematrix_();
    double determinant();
    bool isSquare();

    //  operators

    T& operator()(int rows, int column);
    Matrix operator+(const Matrix& other);
    Matrix operator-(const Matrix& other);
    Matrix operator*(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix& operator*=(const double number);
    bool operator==(const Matrix& other);

    // utilities
    void initMatrix(std::string path);
    void print();

   private:
    // Attributes
    int rows_{}, cols_{};  // Rows and columns
    T** matrix_{};  // Pointer to the memory where the matrix is allocated

    Matrix cutMatrix(int rows, int columns);
    bool validate() const;
    void createMatrix();
    void freeMatrix();
};
#include "matrix.inl"
#endif  // MATRIX_H_
