#include "LinearRegression.h"
#include <fstream>
#include <sstream>
#include <cmath>
#include <cassert>
#include <iostream>
#include <algorithm> // for std::remove_if
#include <cctype>    // for std::isspace

using namespace std;

LinearRegression::LinearRegression(const Matrix& features, const Vector& targets)
    : A(features), b(targets) {
    assert(A.NumRows() == b.Size());
}

void LinearRegression::Train() {
    Matrix At = A.Transpose();
    Matrix AtA = At * A;
    Matrix AtA_inv = AtA.Inverse();
    Matrix pseudoInv = AtA_inv * At;
    coefficients = pseudoInv * b;
}

Vector LinearRegression::Predict(const Matrix& X) const {
    return X * coefficients;
}

double LinearRegression::RMSE(const Vector& predicted, const Vector& actual) const {
    assert(predicted.Size() == actual.Size());
    double sum = 0.0;
    for (int i = 1; i <= predicted.Size(); ++i)
        sum += std::pow(predicted(i) - actual(i), 2);
    return std::sqrt(sum / predicted.Size());
}

Vector LinearRegression::GetCoefficients() const {
    return coefficients;
}

// Helper: trim whitespace from string
std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return ""; // all whitespace
    size_t end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

bool LoadDataset(const std::string& filename, Matrix& features, Vector& targets, int& numTrain) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << "\n";
        return false;
    }

    std::vector<std::vector<double>> featureRows;
    std::vector<double> targetValues;

    std::string line;
    int lineNumber = 0;
    while (std::getline(inFile, line)) {
        ++lineNumber;
        std::stringstream ss(line);
        std::string token;
        std::vector<double> row;

        // Skip first two columns: vendor and model name
        for (int skip = 0; skip < 2; ++skip) {
            if (!std::getline(ss, token, ',')) {
                std::cerr << "Skipping line with missing ID columns at line " << lineNumber << "\n";
                continue;
            }
        }

        // Read next 6 numeric features
        bool rowValid = true;
        for (int i = 0; i < 6; ++i) {
            if (!std::getline(ss, token, ',')) {
                rowValid = false;
                std::cerr << "Not enough features on line " << lineNumber << "\n";
                break;
            }
            token = trim(token);
            try {
                row.push_back(std::stod(token));
            } catch (const std::invalid_argument&) {
                std::cerr << "Invalid feature value '" << token << "' on line " << lineNumber << "\n";
                rowValid = false;
                break;
            }
        }
        if (!rowValid) continue;

        // Read target (last column)
        if (!std::getline(ss, token)) {
            std::cerr << "Missing target value on line " << lineNumber << "\n";
            continue;
        }
        token = trim(token);
        double target;
        try {
            target = std::stod(token);
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid target value '" << token << "' on line " << lineNumber << "\n";
            continue;
        }

        if (row.size() == 6) {
            featureRows.push_back(row);
            targetValues.push_back(target);
        }
    }

    int totalRows = static_cast<int>(featureRows.size());
    if (totalRows == 0) {
        std::cerr << "No valid data found.\n";
        return false;
    }

    // Fill Matrix and Vector
    features = Matrix(totalRows, 6);
    targets = Vector(totalRows);
    for (int i = 0; i < totalRows; ++i) {
        for (int j = 0; j < 6; ++j)
            features(i + 1, j + 1) = featureRows[i][j];
        targets(i + 1) = targetValues[i];
    }

    numTrain = totalRows * 2 / 3; // 2/3 training, 1/3 testing
    return true;
}
