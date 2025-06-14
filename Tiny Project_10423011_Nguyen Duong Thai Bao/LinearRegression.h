#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include "Matrix.h"
#include "Vector.h"
#include <string>
#include <vector>

class LinearRegression {
private:
    Matrix A;
    Vector b;
    Vector coefficients;

public:
    LinearRegression(const Matrix& features, const Vector& targets);
    void Train();
    Vector Predict(const Matrix& X) const;
    double RMSE(const Vector& predicted, const Vector& actual) const;
    Vector GetCoefficients() const;
};

bool LoadDataset(const std::string& filename, Matrix& features, Vector& targets, int& numTrain);

#endif