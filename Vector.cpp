#include "Vector.hpp"

Vector::Vector(int size) {
  mSize = size;
  mData = new float[mSize];
}

Vector::~Vector() {
  delete[] mData;
}

float& Vector::operator()(int index) {
  return mData[index - 1];
}
