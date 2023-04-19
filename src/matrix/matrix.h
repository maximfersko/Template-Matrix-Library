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
    Matrix(std::size_t rows, std::size_t columns);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    explicit Matrix(const std::string filename);
    explicit Matrix(std::initializer_list<T> const& items);
    ~Matrix();

    //  Methods

    int GetRows() const;
    int GetColumns() const;
    void SetRows(std::size_t rows);
    void SetColumns(std::size_t columns);
    bool IsEqualMatrix(const Matrix& other);
    void SumMatrix(const Matrix& other);
    void SubMatrix(const Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const Matrix& other);
    Matrix Transpose();
    Matrix CalcComplements();
    Matrix InverseMatrix();
    double Determinant();
    bool IsSquare();

    //  operators

    T& operator()(std::size_t rows, std::size_t column);
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
    void InitFromFile(std::string path);
    void Print();

   private:
    // Attributes
    std::size_t rows_{}, cols_{};  // Rows and columns
    T** matrix_{};  // Pointer to the memory where the matrix is allocated

    Matrix CutMatrix(std::size_t rows, std::size_t columns);
    bool IsValidate() const;
    void Allocate();
    void Destroy();
};
#include "matrix.inl"
#endif  // MATRIX_H_
