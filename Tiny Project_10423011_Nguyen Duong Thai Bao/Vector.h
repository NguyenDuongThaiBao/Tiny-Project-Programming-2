#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

class Vector {
private:
    int mSize;
    double* mData;

public:
    Vector();
    explicit Vector(int size);
    Vector(const Vector& other);
    ~Vector();

    Vector& operator=(const Vector& other);

    double& operator[](int i);
    double operator[](int i) const;

    double& operator()(int i);
    double operator()(int i) const;

    int Size() const;

    Vector operator+() const;
    Vector operator-() const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;

    friend Vector operator*(double scalar, const Vector& v);

    // Dot product method
    double Dot(const Vector& other) const;
};

#endif // VECTOR_H
