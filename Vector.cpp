#include "Vector.hpp"
#include <iostream>

Vector::Vector(int size) {
  mSize = size;
  mData = new float[mSize];

  for (int i = 0; i < mSize; i++) {
    mData[i] = 0;
  }
}

Vector::~Vector() {
  delete[] mData;
}

void Vector::print() {
  for (int i = 0; i < mSize; i++) {
    std::cout << mData[i] << " ";
  }
  std::cout << std::endl;
}

float& Vector::operator()(int index) {
  return mData[index - 1];
}

Vector Vector::operator+(Vector& other) {
  Vector result(mSize);

  for (int i = 0; i < mSize; i++) {
    result.mData[i] = mData[i] + other.mData[i];
  }

  return result;
}
