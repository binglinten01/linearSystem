#include "Vector.hpp"
#include <cassert>
#include <iostream>

Vector::Vector(int size) {
    assert(size > 0);

    mSize = size;
    mData = new float[mSize];

    for (int i = 0; i < mSize; i++) {
        mData[i] = 0.0f;
    }
}

Vector::Vector(const Vector& other) {
    mSize = other.mSize;
    mData = new float[mSize];

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
    mData = new float[mSize];

    for (int i = 0; i < mSize; i++) {
        mData[i] = other.mData[i];
    }

    return *this;
}

int Vector::getSize() const {
    return mSize;
}

float& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

const float& Vector::operator[](int index) const {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

float& Vector::operator()(int index) {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

const float& Vector::operator()(int index) const {
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

Vector Vector::operator+(float scalar) const {
    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] + scalar;
    }

    return result;
}

Vector Vector::operator-(float scalar) const {
    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] - scalar;
    }

    return result;
}

Vector Vector::operator*(float scalar) const {
    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] * scalar;
    }

    return result;
}

float Vector::operator*(const Vector& other) const {
    assert(mSize == other.mSize);

    float sum = 0.0f;

    for (int i = 0; i < mSize; i++) {
        sum += mData[i] * other.mData[i];
    }

    return sum;
}

void Vector::print() const {
    for (int i = 0; i < mSize; i++) {
        std::cout << mData[i] << " ";
    }

    std::cout << std::endl;
}
