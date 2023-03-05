#include "matrix.h"

template <class T>
Matrix<T>::Matrix() : _rows(2), _cols(2) { createMatrix(); }

template <class T>
Matrix<T>::Matrix(int rows, int columns) : _rows(rows), _cols(columns) {
    if (rows <= 0 || columns <= 0) {
        throw std::out_of_range("Invalid values");
    }
    createMatrix();
}

template <class T>
Matrix<T>::Matrix(const Matrix& other)
    : _rows(other._rows), _cols(other._cols) {
    if (this != &other) {
        createMatrix();
        *this = other;
    }
}

template <class T>
Matrix<T>::Matrix(std::string filename) {
    initMatrix(filename);
}

template <class T>
Matrix<T>::Matrix(Matrix&& other) : _rows(0), _cols(0), _matrix(nullptr) {
    std::swap(_rows, other._rows);
    std::swap(_cols, other._cols);
    std::swap(_matrix, other._matrix);
}

template <class T>
bool Matrix<T>::isSquare() {
    return _rows == _cols;
}

template <class T>
Matrix<T>::~Matrix() { freeMatrix(); }

template <class T>
int Matrix<T>::getRows() const { return _rows; }

template <class T>
int Matrix<T>::getColumn() const { return _cols; }

template <class T>
void Matrix<T>::setRows(int rows) {
    if (rows <= 0) {
        throw std::out_of_range("Invalid values");
    } else {
        Matrix tmp(rows, _cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < _cols; j++) {
                if (i >= _rows) {
                    tmp._matrix[i][j] = 0.0;
                } else {
                    tmp._matrix[i][j] = _matrix[i][j];
                }
            }
        }
        *this = tmp;
    }
}

template <class T>
void Matrix<T>::setColumn(int columns) {
    if (columns <= 0) {
        throw std::out_of_range("Invalid values");
    } else {
        Matrix tmp(_rows, columns);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (j >= _cols) {
                    tmp._matrix[i][j] = 0.0;
                } else {
                    tmp._matrix[i][j] = _matrix[i][j];
                }
            }
        }
        *this = tmp;
    }
}

template <class T>
void Matrix<T>::createMatrix() {
    _matrix = new T*[_rows];
    for (int i = 0; i < _rows; i++) {
        _matrix[i] = new T[_cols]{};
    }
}

template <class T>
void Matrix<T>::freeMatrix() {
    if (_matrix) {
        for (int i = 0; i < _rows; i++) {
            if (_matrix[i]) delete[] _matrix[i];
        }
        delete[] _matrix;
        _matrix = nullptr;
    }
    _rows = 0;
    _cols = 0;
}

template <class T>
bool Matrix<T>::eq_matrix(const Matrix& other) {
    bool result = true;
    if (_cols != other._cols || _rows != other._rows || !this->validate() ||
        !other.validate()) {
        result = false;
    } else {
        double equal;
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                equal = std::fabs(_matrix[i][j] - other._matrix[i][j]);
                if (equal > 1E-7) {
                    result = false;
                    break;
                }
            }
            if (!result) break;
        }
    }
    return result;
}

template <class T>
void Matrix<T>::sum_matrix(const Matrix& other) {
    if (_cols != other._cols || _rows != other._rows || !this->validate() ||
        !other.validate()) {
        throw std::out_of_range("Error ! Different dimensionality of matrices");
    } else {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                _matrix[i][j] = other._matrix[i][j] + _matrix[i][j];
            }
        }
    }
}

template <class T>
void Matrix<T>::sub_matrix(const Matrix& other) {
    if (_cols != other._cols || _rows != other._rows || !this->validate() ||
        !other.validate()) {
        throw std::out_of_range("Error ! Different dimensionality of matrices");
    } else {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                _matrix[i][j] = _matrix[i][j] - other._matrix[i][j];
            }
        }
    }
}

template <class T>
void Matrix<T>::mul_number(const double num) {
    if (std::isnan(num) || std::isinf(num)) {
        throw std::out_of_range("Incorrect values");
    } else {
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                _matrix[i][j] = _matrix[i][j] * num;
            }
        }
    }
}

template <class T>
void Matrix<T>::mul_matrix(const Matrix& other) {
    if (this->_rows != other._cols || !this->validate() || !other.validate()) {
        throw std::out_of_range("Error ! Invalid values");
    } else {
        Matrix tmp(_rows, other._cols);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < other._cols; j++) {
                for (int k = 0; k < _cols; k++) {
                    tmp._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
                }
            }
        }
        *this = tmp;
    }
}

template <class T>
Matrix<T> Matrix<T>::transpose() {
    Matrix result(_cols, _rows);
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            result._matrix[j][i] = _matrix[i][j];
        }
    }
    return result;
}

template <class T>
double Matrix<T>::determinant() {
    double result = 0.0;
    if (_rows != _cols || !this->validate()) {
        throw std::out_of_range("Error ! The matrix must not be square !");
    } else {
        if (_rows == 1) {
            result = _matrix[0][0];
        } else if (_rows == 2) {
            result = (_matrix[1][1] * _matrix[0][0]) -
                     (_matrix[1][0] * _matrix[0][1]);
        } else if (_rows > 2) {
            for (int i = 0; i < _rows; i++) {
                Matrix detA = cutMatrix(0, i);
                result +=
                    std::pow(-1.0, i) * _matrix[0][i] * detA.determinant();
            }
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::cutMatrix(int rows, int columns) {
    Matrix result(_rows - 1, _cols - 1);
    int rowsTmp = 0, columnsTmp = 0;
    for (int i = 0; i < _rows; i++) {
        if (rows != i) {
            for (int j = 0; j < _cols; j++) {
                if (columns != j) {
                    result._matrix[rowsTmp][columnsTmp] = _matrix[i][j];
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
    Matrix result(_rows, _cols);
    if (_cols != _rows || !this->validate()) {
        throw std::out_of_range("Error ! The matrix must not be square !");
    } else {
        Matrix tmp;
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _rows; j++) {
                tmp = cutMatrix(i, j);
                result._matrix[i][j] = std::pow(-1, i + j) * tmp.determinant();
            }
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::inverse_matrix() {
    double det = determinant();
    if (_cols != _rows || std::isnan(det) || det == 0 ||
        !this->validate()) {
        throw std::out_of_range("Error ! The determinant of the matrix is 0");
    } 
    Matrix result = Matrix(_rows, _cols);
    if (_rows == 1) {
        result._matrix[0][0] = 1 / det;
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
    if (_cols <= column || _rows <= rows || rows < 0 || column < 0) {
        throw std::out_of_range("Incorrect values");
    }
    return _matrix[rows][column];
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) {
    Matrix result(*this);
    result.sum_matrix(other);
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) {
    Matrix result(*this);
    result.sub_matrix(other);
    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) {
    Matrix result(*this);
    result.mul_matrix(other);
    return result;
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T>& other) { return eq_matrix(other); }

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (this != &other) {
        freeMatrix();
        _rows = other._rows;
        _cols = other._cols;
        createMatrix();
    }
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) {
    if (this != &other) {
        freeMatrix();
        _rows = other._rows;
        _cols = other._cols;
        _matrix = other._matrix;
        other._matrix = nullptr;
        other._cols = other._rows = 0;
    }
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    sum_matrix(other);
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    sub_matrix(other);
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& other) {
    mul_matrix(other);
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const double number) {
    mul_number(number);
    return *this;
}

template <class T>
Matrix<T> operator*(const Matrix<T>& other, const double num) {
    if (std::isnan(num) || std::isinf(num)) {
        throw std::out_of_range("Incorrect values");
    }
    Matrix result(other.getRows(), other.getColumn());
    result = other;
    result *= num;
    return result;
}

template <class T>
Matrix<T> operator*(const double num, const Matrix<T>& other) {
    if (std::isnan(num) || std::isinf(num)) {
        throw std::out_of_range("Incorrect values");
    }
    Matrix result(other.getRows(), other.getColumn());
    result = other;
    result *= num;
    return result;
}

template <class T>
void Matrix<T>::initMatrix(std::string path) {
    std::ifstream file(path);
    if (file) {
        std::string line;
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                file >> _matrix[i][j];
            }
        }
        file.close();
    } else {
        throw std::out_of_range("file error");
    }
}

template <class T>
bool Matrix<T>::validate() const {
    bool result = false;
    if (this->_matrix != nullptr || this->_rows > 0 || this->_cols > 0) {
        result = true;
    }
    return result;
}

template <class T>
void Matrix<T>::print() {
    std::cout << std::endl;
    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            std::cout << _matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}