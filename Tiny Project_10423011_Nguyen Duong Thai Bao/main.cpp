// to run this, open terminal, write g++ main.cpp LinearSystem.cpp PosSymLinSystem.cpp Matrix.cpp Vector.cpp LinearRegression.cpp -std=c++11 -o tiny_project
// and then write ./tiny_project
// main.cpp
#include "LinearRegression.h"
#include <iostream>

int main() {
    Matrix features;
    Vector targets;
    int numTrain;

    if (!LoadDataset("machine.data", features, targets, numTrain)) {
        std::cerr << "Failed to load dataset.\n";
        return 1;
    }

    // Split into training and testing
    Matrix X_train(numTrain, 6);
    Vector y_train(numTrain);
    Matrix X_test(features.NumRows() - numTrain, 6);
    Vector y_test(features.NumRows() - numTrain);

    for (int i = 1; i <= numTrain; ++i) {
        for (int j = 1; j <= 6; ++j)
            X_train(i, j) = features(i, j);
        y_train(i) = targets(i);
    }

    for (int i = numTrain + 1; i <= features.NumRows(); ++i) {
        for (int j = 1; j <= 6; ++j)
            X_test(i - numTrain, j) = features(i, j);
        y_test(i - numTrain) = targets(i);
    }

    // Train the model
    LinearRegression model(X_train, y_train);
    model.Train();

    // Predict and evaluate
    Vector predictions = model.Predict(X_test);
    double rmse = model.RMSE(predictions, y_test);

    std::cout << "Root Mean Squared Error on Test Set: " << rmse << "\n";
    std::cout << "Learned coefficients:\n";
    Vector coeffs = model.GetCoefficients();
    for (int i = 1; i <= coeffs.Size(); ++i)
        std::cout << "x" << i << " = " << coeffs(i) << "\n";

    return 0;
}
