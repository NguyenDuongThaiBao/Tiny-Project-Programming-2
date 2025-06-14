#include "Matrix.h"
#include <cassert>
#include <cmath>
#include "Vector.h"

// Default constructor
Matrix::Matrix() : mNumRows(0), mNumCols(0), mData(nullptr) {}

void Matrix::AllocateMemory() {
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i)
        mData[i] = new double[mNumCols]{};
}

void Matrix::FreeMemory() {
    if (mData) {
        for (int i = 0; i < mNumRows; ++i)
            delete[] mData[i];
        delete[] mData;
        mData = nullptr;
    }
}

Matrix::Matrix(int numRows, int numCols) : mNumRows(numRows), mNumCols(numCols) {
    assert(numRows > 0 && numCols > 0);
    AllocateMemory();
}

Matrix::Matrix(const Matrix& other)
    : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    AllocateMemory();
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
}

Matrix::~Matrix() {
    FreeMemory();
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;
    FreeMemory();
    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;
    AllocateMemory();
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
    return *this;
}

double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

double Matrix::operator()(int i, int j) const {
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

int Matrix::NumRows() const { return mNumRows; }
int Matrix::NumCols() const { return mNumCols; }

Matrix Matrix::operator+(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] + other.mData[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] - other.mData[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    assert(mNumCols == other.mNumRows);
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < other.mNumCols; ++j)
            for (int k = 0; k < mNumCols; ++k)
                result.mData[i][j] += mData[i][k] * other.mData[k][j];
    return result;
}

Vector Matrix::operator*(const Vector& v) const {
    assert(mNumCols == v.Size());
    Vector result(mNumRows);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result(i + 1) += mData[i][j] * v(j + 1);
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[i][j] = mData[i][j] * scalar;
    return result;
}

Matrix Matrix::Transpose() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result.mData[j][i] = mData[i][j];
    return result;
}

// Inverse using Gauss-Jordan elimination
Matrix Matrix::Inverse() const {
    assert(mNumRows == mNumCols);
    int n = mNumRows;
    Matrix A(*this);
    Matrix I(n, n);

    for (int i = 1; i <= n; ++i)
        I(i, i) = 1.0;

    for (int i = 1; i <= n; ++i) {
        double pivot = A(i, i);
        assert(std::fabs(pivot) > 1e-10); // prevent division by zero
        for (int j = 1; j <= n; ++j) {
            A(i, j) /= pivot;
            I(i, j) /= pivot;
        }
        for (int k = 1; k <= n; ++k) {
            if (k == i) continue;
            double factor = A(k, i);
            for (int j = 1; j <= n; ++j) {
                A(k, j) -= factor * A(i, j);
                I(k, j) -= factor * I(i, j);
            }
        }
    }
    return I;
}
