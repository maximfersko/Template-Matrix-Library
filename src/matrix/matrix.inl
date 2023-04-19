#include "matrix.h"

template <class T>
Matrix<T>::Matrix() : rows_(2), cols_(2) {
    Allocate();
}

template <class T>
Matrix<T>::Matrix(int rows, int columns) : rows_(rows), cols_(columns) {
    if (rows <= 0 || columns <= 0) throw std::out_of_range("Invalid values");
    Allocate();
}

template <class T>
Matrix<T>::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
    if (this != &other) {
        Allocate();
        *this = other;
    }
}

template <class T>
Matrix<T>::Matrix(std::initializer_list<T> const& items) {
    rows_ = cols_ = sqrt(items.size());
    Allocate();
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
    InitFromFile(filename);
}

template <class T>
Matrix<T>::Matrix(Matrix&& other)
    : matrix_(other.matrix_), cols_(other.GetColumns()), rows_(other.GetRows()) {
    other.matrix_ = nullptr;
}

template <class T>
bool Matrix<T>::IsSquare() {
    return rows_ == cols_;
}

template <class T>
Matrix<T>::~Matrix() {
    Destroy();
}

template <class T>
int Matrix<T>::GetRows() const {
    return rows_;
}

template <class T>
int Matrix<T>::GetColumns() const {
    return cols_;
}

template <class T>
void Matrix<T>::SetRows(int rows) {
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
void Matrix<T>::SetColumns(int columns) {
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
void Matrix<T>::Allocate() {
    matrix_ = new T* [rows_] {};
    for (int i = 0; i < rows_; i++) matrix_[i] = new T[cols_]{};
}

template <class T>
void Matrix<T>::Destroy() {
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
bool Matrix<T>::IsEqualMatrix(const Matrix& other) {
    if (cols_ != other.cols_ || rows_ != other.rows_ || !this->IsValidate() ||
        !other.IsValidate())
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
void Matrix<T>::SumMatrix(const Matrix& other) {
    if (cols_ != other.cols_ || rows_ != other.rows_ || !this->IsValidate() ||
        !other.IsValidate())
        throw std::out_of_range("Error ! Different dimensionality of matrices");
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = other.matrix_[i][j] + matrix_[i][j];
        }
    }
}

template <class T>
void Matrix<T>::SubMatrix(const Matrix& other) {
    if (cols_ != other.cols_ || rows_ != other.rows_ || !this->IsValidate() ||
        !other.IsValidate())
        throw std::out_of_range("Error ! Different dimensionality of matrices");
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
        }
    }
}

template <class T>
void Matrix<T>::MulNumber(const double num) {
    if (std::isnan(num) || std::isinf(num))
        throw std::out_of_range("Incorrect values");
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            matrix_[i][j] = matrix_[i][j] * num;
        }
    }
}

template <class T>
void Matrix<T>::MulMatrix(const Matrix& other) {
    if (this->rows_ != other.cols_ || !this->IsValidate() || !other.IsValidate())
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
Matrix<T> Matrix<T>::Transpose() {
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            result.matrix_[j][i] = matrix_[i][j];
        }
    }
    return result;
}

template <class T>
double Matrix<T>::Determinant() {
    double result = 0.0;
    if (rows_ != cols_ || !this->IsValidate())
        throw std::out_of_range("Error ! The matrix must not be square !");
    if (rows_ == 1) {
        result = matrix_[0][0];
    } else if (rows_ == 2) {
        result =
            (matrix_[1][1] * matrix_[0][0]) - (matrix_[1][0] * matrix_[0][1]);
    } else if (rows_ > 2) {
        for (int i = 0; i < rows_; i++) {
            Matrix detA = CutMatrix(0, i);
            result += std::pow(-1.0, i) * matrix_[0][i] * detA.Determinant();
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::CutMatrix(int rows, int columns) {
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
Matrix<T> Matrix<T>::CalcComplements() {
    Matrix result(rows_, cols_);
    if (cols_ != rows_ || !this->IsValidate())
        throw std::out_of_range("Error ! The matrix must not be square !");
    Matrix tmp;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < rows_; j++) {
            tmp = CutMatrix(i, j);
            result.matrix_[i][j] = std::pow(-1, i + j) * tmp.Determinant();
        }
    }
    return result;
}

template <class T>
Matrix<T> Matrix<T>::InverseMatrix() {
    double det = Determinant();
    if (cols_ != rows_ || std::isnan(det) || det == 0 || !this->IsValidate())
        throw std::out_of_range("Error ! The Determinant of the matrix is 0");
    Matrix result = Matrix(rows_, cols_);
    if (rows_ == 1) {
        result.matrix_[0][0] = 1 / det;
    } else {
        Matrix complements = CalcComplements();
        Matrix Transpose = complements.Transpose();
        Transpose.MulNumber(1 / det);
        result = Transpose;
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
        Destroy();
        rows_ = other.rows_;
        cols_ = other.cols_;
        Allocate();
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
        Destroy();
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
    MulNumber(number);
    return *this;
}

template <class T>
Matrix<T> operator*(const Matrix<T>& other, const double num) {
    if (std::isnan(num) || std::isinf(num))
        throw std::out_of_range("Incorrect values");
    Matrix result(other.GetRows(), other.GetColumns());
    result = other;
    result *= num;
    return result;
}

template <class T>
Matrix<T> operator*(const double num, const Matrix<T>& other) {
    if (std::isnan(num) || std::isinf(num))
        throw std::out_of_range("Incorrect values");
    Matrix result(other.GetRows(), other.GetColumns());
    result = other;
    result *= num;
    return result;
}

template <class T>
void Matrix<T>::InitFromFile(std::string path) {
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
bool Matrix<T>::IsValidate() const {
    bool result = false;
    if (this->matrix_ != nullptr || this->rows_ > 0 || this->cols_ > 0) {
        result = true;
    }
    return result;
}

template <class T>
void Matrix<T>::Print() {
    std::cout << std::endl;
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) std::cout << matrix_[i][j] << " ";
        std::cout << std::endl;
    }
}