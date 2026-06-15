#include "Vector.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

Vector::Vector(int size) {
    assert(size > 0);

    mSize = size;
    mData = new double[mSize];

    for (int i = 0; i < mSize; i++) {
        mData[i] = 0.0;
    }
}

Vector::Vector(const Vector& other) {
    mSize = other.mSize;
    mData = new double[mSize];

    for (int i = 0; i < mSize; i++) {
        mData[i] = other.mData[i];
    }
}

Vector::~Vector() {
    delete[] mData;
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    delete[] mData;

    mSize = other.mSize;
    mData = new double[mSize];

    for (int i = 0; i < mSize; i++) {
        mData[i] = other.mData[i];
    }

    return *this;
}

int Vector::getSize() const {
    return mSize;
}

double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

const double& Vector::operator[](int index) const {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

double& Vector::operator()(int index) {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

const double& Vector::operator()(int index) const {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

Vector Vector::operator+() const {
    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i];
    }

    return result;
}

Vector Vector::operator-() const {
    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = -mData[i];
    }

    return result;
}

Vector Vector::operator+(const Vector& other) const {
    assert(mSize == other.mSize);

    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] + other.mData[i];
    }

    return result;
}

Vector Vector::operator-(const Vector& other) const {
    assert(mSize == other.mSize);

    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] - other.mData[i];
    }

    return result;
}

Vector Vector::operator+(double scalar) const {
    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] + scalar;
    }

    return result;
}

Vector Vector::operator-(double scalar) const {
    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] - scalar;
    }

    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] * scalar;
    }

    return result;
}

Vector Vector::operator/(double scalar) const {
    assert(std::fabs(scalar) > 1e-14);

    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] / scalar;
    }

    return result;
}

Vector& Vector::operator+=(const Vector& other) {
    assert(mSize == other.mSize);

    for (int i = 0; i < mSize; i++) {
        mData[i] += other.mData[i];
    }

    return *this;
}

Vector& Vector::operator-=(const Vector& other) {
    assert(mSize == other.mSize);

    for (int i = 0; i < mSize; i++) {
        mData[i] -= other.mData[i];
    }

    return *this;
}

Vector& Vector::operator*=(double scalar) {
    for (int i = 0; i < mSize; i++) {
        mData[i] *= scalar;
    }

    return *this;
}

Vector& Vector::operator/=(double scalar) {
    assert(std::fabs(scalar) > 1e-14);

    for (int i = 0; i < mSize; i++) {
        mData[i] /= scalar;
    }

    return *this;
}

double Vector::operator*(const Vector& other) const {
    assert(mSize == other.mSize);

    double result = 0.0;

    for (int i = 0; i < mSize; i++) {
        result += mData[i] * other.mData[i];
    }

    return result;
}

double Vector::norm() const {
    return std::sqrt((*this) * (*this));
}

void Vector::print() const {
    for (int i = 0; i < mSize; i++) {
        std::cout << mData[i] << " ";
    }

    std::cout << std::endl;
}

Vector operator+(double scalar, const Vector& v) {
    return v + scalar;
}

Vector operator-(double scalar, const Vector& v) {
    Vector result(v.mSize);

    for (int i = 0; i < v.mSize; i++) {
        result.mData[i] = scalar - v.mData[i];
    }

    return result;
}

Vector operator*(double scalar, const Vector& v) {
    return v * scalar;
}
