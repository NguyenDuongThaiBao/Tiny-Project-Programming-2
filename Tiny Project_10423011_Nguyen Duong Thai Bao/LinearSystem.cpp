#include <algorithm>
#include "LinearSystem.h"
#include <cassert>
#include <cmath>

// --- LinearSystem Implementation ---

LinearSystem::LinearSystem(const Matrix& A, const Vector& b)
{
    assert(A.NumRows() == A.NumCols());
    assert(A.NumRows() == b.Size());

    mSize = A.NumRows();
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

// Gaussian elimination with partial pivoting
Vector LinearSystem::Solve() {
    Matrix A(*mpA);
    Vector b(*mpb);
    int n = mSize;

    for (int k = 0; k < n; ++k) {
        // Partial pivoting
        int maxRow = k;
        for (int i = k + 1; i < n; ++i)
            if (std::fabs(A(i+1, k+1)) > std::fabs(A(maxRow+1, k+1)))
                maxRow = i;

        for (int j = 0; j < n; ++j)
            std::swap(A(k+1, j+1), A(maxRow+1, j+1));
        std::swap(b(k+1), b(maxRow+1));

        // Elimination
        for (int i = k + 1; i < n; ++i) {
            double factor = A(i+1, k+1) / A(k+1, k+1);
            for (int j = k; j < n; ++j)
                A(i+1, j+1) -= factor * A(k+1, j+1);
            b(i+1) -= factor * b(k+1);
        }
    }

    // Back substitution
    Vector x(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = b(i+1);
        for (int j = i + 1; j < n; ++j)
            sum -= A(i+1, j+1) * x(j+1);
        x(i+1) = sum / A(i+1, i+1);
    }

    return x;
}
