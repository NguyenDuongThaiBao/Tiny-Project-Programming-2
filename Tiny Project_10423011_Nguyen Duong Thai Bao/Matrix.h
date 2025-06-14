#ifndef MATRIX_H
#define MATRIX_H

#include <cassert>
#include "Vector.h"

class Matrix {
private:
    int mNumRows, mNumCols;
    double** mData;

    void AllocateMemory();
    void FreeMemory();

public:
    Matrix();
    Matrix(int numRows, int numCols);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);

    double& operator()(int i, int j);
    double operator()(int i, int j) const;

    int NumRows() const;
    int NumCols() const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Vector operator*(const Vector& v) const;
    Matrix operator*(double scalar) const;

    Matrix Transpose() const;
    Matrix Inverse() const;
};

#endif // MATRIX_H