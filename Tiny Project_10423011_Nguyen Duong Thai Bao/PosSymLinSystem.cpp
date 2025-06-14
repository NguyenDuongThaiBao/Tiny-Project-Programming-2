#include <cassert>
#include <cmath>  // for std::fabs, std::sqrt
#include "PosSymLinSystem.h"  // your header

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b)
{
    for (int i = 1; i <= mSize; ++i)
        for (int j = 1; j <= mSize; ++j)
            assert(std::fabs((*mpA)(i,j) - (*mpA)(j,i)) < 1e-10);
}

// Conjugate Gradient Method
Vector PosSymLinSystem::Solve() {
    Vector x(mSize);
    Vector r = *mpb - (*mpA) * x;
    Vector p = r;
    Vector Ap(mSize);

    double tol = 1e-10;
    int maxIter = mSize * 10;

    for (int k = 0; k < maxIter; ++k) {
        Ap = (*mpA) * p;
        double alpha = r.Dot(r) / p.Dot(Ap);
        x = x + alpha * p;
        Vector r_new = r - alpha * Ap;

        if (std::sqrt(r_new.Dot(r_new)) < tol)
            break;

        double beta = r_new.Dot(r_new) / r.Dot(r);
        p = r_new + beta * p;
        r = r_new;
    }

    return x;
}
