#include "Vector.h"

// Default constructor
Vector::Vector() : mSize(0), mData(nullptr) {}

// Constructor with size
Vector::Vector(int size) : mSize(size) {
    assert(size > 0);
    mData = new double[mSize]{0};
}

// Copy constructor
Vector::Vector(const Vector& other) : mSize(other.mSize) {
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i)
        mData[i] = other.mData[i];
}

// Destructor
Vector::~Vector() {
    delete[] mData;
}

// Assignment operator
Vector& Vector::operator=(const Vector& other) {
    if (this == &other)
        return *this;
    delete[] mData;
    mSize = other.mSize;
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i)
        mData[i] = other.mData[i];
    return *this;
}

double& Vector::operator[](int i) {
    assert(i >= 0 && i < mSize);
    return mData[i];
}

double Vector::operator[](int i) const {
    assert(i >= 0 && i < mSize);
    return mData[i];
}

double& Vector::operator()(int i) {
    assert(i >= 1 && i <= mSize);
    return mData[i - 1];
}

double Vector::operator()(int i) const {
    assert(i >= 1 && i <= mSize);
    return mData[i - 1];
}

int Vector::Size() const {
    return mSize;
}

Vector Vector::operator+() const {
    return *this;
}

Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = -mData[i];
    return result;
}

Vector Vector::operator+(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] + other.mData[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] - other.mData[i];
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] * scalar;
    return result;
}

Vector operator*(double scalar, const Vector& v) {
    return v * scalar;
}

// Dot product
double Vector::Dot(const Vector& other) const {
    assert(mSize == other.mSize);
    double sum = 0.0;
    for (int i = 0; i < mSize; ++i)
        sum += mData[i] * other.mData[i];
    return sum;
}
