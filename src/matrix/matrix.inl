#include "matrix.h"

template <class T>
Matrix<T>::Matrix() : rows_(2), cols_(2) {
    createMatrix();
}

template <class T>
Matrix<T>::Matrix(int rows, int columns) : rows_(rows), cols_(columns) {
    if (rows <= 0 || columns <= 0) throw std::out_of_range("Invalid values");
    createMatrix();
}

template <class T>
Matrix<T>::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
    if (this != &other) {
        createMatrix();
        *this = other;
    }
}

template <class T>
Matrix<T>::Matrix(std::initializer_list<T> const& items) {
    rows_ = cols_ = sqrt(items.size());
    createMatrix();
    auto iterator = items.begin();
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            matrix_[i][j] = *iterator;
            iterator++;
        }
    }
}

template <class T>
Matrix<T>::Matrix(const std::string filename) {
    initMatrix(filename);
}

template <class T>
Matrix<T>::Matrix(Matrix&& other)
    : matrix_(other.matrix_), cols_(other.getColumn()), rows_(other.getRows()) {
    other.matrix_ = nullptr;
}

template <class T>
bool Matrix<T>::isSquare() {
    return rows_ == cols_;
}

template <class T>
Matrix<T>::~Matrix() {
    freeMatrix();
}

template <class T>
int Matrix<T>::getRows() const {
    return rows_;
}

template <class T>
int Matrix<T>::getColumn() const {
    return cols_;
}

template <class T>
void Matrix<T>::setRows(int rows) {
    if (rows <= 0) throw std::out_of_range("Invalid values");
    Matrix tmp(rows, cols_);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols_; j++) {
            if (i >= rows_) {
                tmp.matrix_[i][j] = 0.0;
            } else {
                tmp.matrix_[i][j] = matrix_[i][j];
            }
        }
    }
    *this = tmp;
}

template <class T>
void Matrix<T>::setColumn(int columns) {
    if (columns <= 0) throw std::out_of_range("Invalid values");
    Matrix tmp(rows_, columns);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns; j++) {
            if (j >= cols_) {
                tmp.matrix_[i][j] = 0.0;
            } else {
                tmp.matrix_[i][j] = matrix_[i][j];
            }
        }
    }
    *this = tmp;
}

template <class T>
void Matrix<T>::createMatrix() {
    matrix_ = new T* [rows_] {};
    for (int i = 0; i < rows_; i++) matrix_[i] = new T[cols_]{};
}

template <class T>
void Matrix<T>::freeMatrix() {
    if (matrix_) {
        for (int i = 0; i < rows_; i++)
            if (matrix_[i]) delete[] matrix_[i];

        delete[] matrix_;
        matrix_ = nullptr;
    }
    rows_ = 0;
    cols_ = 0;
}

template <class T>
bool Matrix<T>::matrix_eq(const Matrix& other) {
    if (cols_ != other.cols_ || rows_ != other.rows_ || !this->validate() ||
        !other.validate())
        return false;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            double equal = std::fabs(matrix_[i][j] - other.matrix_[i][j]);
            if (equal > 1E-7) return false;
        }
    }
    return true;
}

template <class T>
void Matrix<T>::matrix_sum(const Matrix& other) {
    if (cols_ != other.cols_ || rows_ != other.rows_ || !this->validate() ||
        !other.validate())
        throw std::out_of_range("Error ! Different dimensionality of matrices");
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = other.matrix_[i][j] + matrix_[i][j];
        }
    }
}

template <class T>
void Matrix<T>::matrix_sub(const Matrix& other) {
    if (cols_ != other.cols_ || rows_ != other.rows_ || !this->validate() ||
        !other.validate())
        throw std::out_of_range("Error ! Different dimensionality of matrices");
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
        }
    }
}

template <class T>
void Matrix<T>::mul_number(const double num) {
    if (std::isnan(num) || std::isinf(num))
        throw std::out_of_range("Incorrect values");
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] * num;
        }
    }
}

template <class T>
void Matrix<T>::matrix_mul(const Matrix& other) {
    if (this->rows_ != other.cols_ || !this->validate() || !other.validate())
        throw std::out_of_range("Error ! Invalid values");
    Matrix tmp(rows_, other.cols_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            for (int k = 0; k < cols_; k++) {
                tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
            }
        }
    }
    *this = tmp;
}

template <class T>
Matrix<T> Matrix<T>::transpose() {
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result;
}

template <class T>
double Matrix<T>::determinant() {
    double result = 0.0;
    if (rows_ != cols_ || !this->validate())
        throw std::out_of_range("Error ! The matrix must not be square !");
    if (rows_ == 1) {
        result = matrix_[0][0];
    } else if (rows_ == 2) {
        result =
            (matrix_[1][1] * matrix_[0][0]) - (matrix_[1][0] * matrix_[0][1]);
    } else if (rows_ > 2) {
        for (int i = 0; i < rows_; i++) {
            Matrix detA = cutMatrix(0, i);
            result += std::pow(-1.0, i) * matrix_[0][i] * detA.determinant();
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::cutMatrix(int rows, int columns) {
    Matrix result(rows_ - 1, cols_ - 1);
    int rowsTmp = 0, columnsTmp = 0;
    for (int i = 0; i < rows_; i++) {
        if (rows != i) {
            for (int j = 0; j < cols_; j++) {
                if (columns != j) {
                    result.matrix_[rowsTmp][columnsTmp] = matrix_[i][j];
                    columnsTmp++;
                }
            }
            columnsTmp = 0;
            rowsTmp++;
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::calc_complements() {
    Matrix result(rows_, cols_);
    if (cols_ != rows_ || !this->validate())
        throw std::out_of_range("Error ! The matrix must not be square !");
    Matrix tmp;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < rows_; j++) {
            tmp = cutMatrix(i, j);
            result.matrix_[i][j] = std::pow(-1, i + j) * tmp.determinant();
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::inversematrix_() {
    double det = determinant();
    if (cols_ != rows_ || std::isnan(det) || det == 0 || !this->validate())
        throw std::out_of_range("Error ! The determinant of the matrix is 0");
    Matrix result = Matrix(rows_, cols_);
    if (rows_ == 1) {
        result.matrix_[0][0] = 1 / det;
    } else {
        Matrix complements = calc_complements();
        Matrix transpose = complements.transpose();
        transpose.mul_number(1 / det);
        result = transpose;
    }
    return result;
}

template <class T>
T& Matrix<T>::operator()(int rows, int column) {
    if (cols_ <= column || rows_ <= rows || rows < 0 || column < 0)
        throw std::out_of_range("Incorrect values");
    return matrix_[rows][column];
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) {
    Matrix result(*this);
    result.summatrix_(other);
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) {
    Matrix result(*this);
    result.submatrix_(other);
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) {
    Matrix result(*this);
    result.mulmatrix_(other);
    return result;
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T>& other) {
    return eqmatrix_(other);
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (this != &other) {
        freeMatrix();
        rows_ = other.rows_;
        cols_ = other.cols_;
        createMatrix();
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) {
    if (this != &other) {
        freeMatrix();
        rows_ = other.rows_;
        cols_ = other.cols_;
        matrix_ = other.matrix_;
        other.matrix_ = nullptr;
        other.cols_ = other.rows_ = 0;
    }
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    summatrix_(other);
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    submatrix_(other);
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
    mulmatrix_(other);
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const double number) {
    mul_number(number);
    return *this;
}

template <class T>
Matrix<T> operator*(const Matrix<T>& other, const double num) {
    if (std::isnan(num) || std::isinf(num))
        throw std::out_of_range("Incorrect values");
    Matrix result(other.getRows(), other.getColumn());
    result = other;
    result *= num;
    return result;
}

template <class T>
Matrix<T> operator*(const double num, const Matrix<T>& other) {
    if (std::isnan(num) || std::isinf(num))
        throw std::out_of_range("Incorrect values");
    Matrix result(other.getRows(), other.getColumn());
    result = other;
    result *= num;
    return result;
}

template <class T>
void Matrix<T>::initMatrix(std::string path) {
    std::ifstream file(path);
    if (!file) throw std::out_of_range("file error");
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            file >> matrix_[i][j];
        }
    }
    file.close();
}

template <class T>
bool Matrix<T>::validate() const {
    bool result = false;
    if (this->matrix_ != nullptr || this->rows_ > 0 || this->cols_ > 0) {
        result = true;
    }
    return result;
}

template <class T>
void Matrix<T>::print() {
    std::cout << std::endl;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) std::cout << matrix_[i][j] << " ";
        std::cout << std::endl;
    }
}