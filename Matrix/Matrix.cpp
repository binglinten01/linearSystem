#include "Matrix.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

Matrix::Matrix(int numRows, int numCols) {
  assert(numRows > 0);
  assert(numCols > 0);

  mNumRows = numRows;
  mNumCols = numCols;

  mData = new float *[mNumRows];

  for (int i = 0; i < mNumRows; i++) {
    mData[i] = new float[mNumCols];

    for (int j = 0; j < mNumCols; j++) {
      mData[i][j] = 0.0f;
    }
  }
}

Matrix::Matrix(const Matrix &other) {
  mNumRows = other.mNumRows;
  mNumCols = other.mNumCols;

  mData = new float *[mNumRows];

  for (int i = 0; i < mNumRows; i++) {
    mData[i] = new float[mNumCols];

    for (int j = 0; j < mNumCols; j++) {
      mData[i][j] = other.mData[i][j];
    }
  }
}

Matrix::~Matrix() {
  for (int i = 0; i < mNumRows; i++) {
    delete[] mData[i];
  }

  delete[] mData;
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this == &other) {
    return *this;
  }

  for (int i = 0; i < mNumRows; i++) {
    delete[] mData[i];
  }
  delete[] mData;

  mNumRows = other.mNumRows;
  mNumCols = other.mNumCols;

  mData = new float *[mNumRows];

  for (int i = 0; i < mNumRows; i++) {
    mData[i] = new float[mNumCols];

    for (int j = 0; j < mNumCols; j++) {
      mData[i][j] = other.mData[i][j];
    }
  }

  return *this;
}

int Matrix::getNumRows() const {
  return mNumRows;
}

int Matrix::getNumCols() const {
  return mNumCols;
}

float &Matrix::operator()(int i, int j) {
  assert(i >= 1 && i <= mNumRows);
  assert(j >= 1 && j <= mNumCols);

  return mData[i - 1][j - 1];
}

const float &Matrix::operator()(int i, int j) const {
  assert(i >= 1 && i <= mNumRows);
  assert(j >= 1 && j <= mNumCols);

  return mData[i - 1][j - 1];
}

Matrix Matrix::operator+() const {
  Matrix result(mNumRows, mNumCols);

  for (int i = 0; i < mNumRows; i++) {
    for (int j = 0; j < mNumCols; j++) {
      result.mData[i][j] = mData[i][j];
    }
  }

  return result;
}

Matrix Matrix::operator-() const {
  Matrix result(mNumRows, mNumCols);

  for (int i = 0; i < mNumRows; i++) {
    for (int j = 0; j < mNumCols; j++) {
      result.mData[i][j] = -mData[i][j];
    }
  }

  return result;
}

Matrix Matrix::operator+(const Matrix &other) const {
  assert(mNumRows == other.mNumRows);
  assert(mNumCols == other.mNumCols);

  Matrix result(mNumRows, mNumCols);

  for (int i = 0; i < mNumRows; i++) {
    for (int j = 0; j < mNumCols; j++) {
      result.mData[i][j] = mData[i][j] + other.mData[i][j];
    }
  }

  return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
  assert(mNumRows == other.mNumRows);
  assert(mNumCols == other.mNumCols);

  Matrix result(mNumRows, mNumCols);

  for (int i = 0; i < mNumRows; i++) {
    for (int j = 0; j < mNumCols; j++) {
      result.mData[i][j] = mData[i][j] - other.mData[i][j];
    }
  }

  return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
  assert(mNumCols == other.mNumRows);

  Matrix result(mNumRows, other.mNumCols);

  for (int i = 0; i < mNumRows; i++) {
    for (int j = 0; j < other.mNumCols; j++) {
      float sum = 0.0f;

      for (int k = 0; k < mNumCols; k++) {
        sum += mData[i][k] * other.mData[k][j];
      }

      result.mData[i][j] = sum;
    }
  }

  return result;
}

Vector Matrix::operator*(const Vector &v) const {
  assert(mNumCols == v.getSize());

  Vector result(mNumRows);

  for (int i = 1; i <= mNumRows; i++) {
    float sum = 0.0f;

    for (int j = 1; j <= mNumCols; j++) {
      sum += (*this)(i, j) * v(j);
    }

    result(i) = sum;
  }

  return result;
}

Matrix Matrix::operator+(float scalar) const {
  Matrix result(mNumRows, mNumCols);

  for (int i = 0; i < mNumRows; i++) {
    for (int j = 0; j < mNumCols; j++) {
      result.mData[i][j] = mData[i][j] + scalar;
    }
  }

  return result;
}

Matrix Matrix::operator-(float scalar) const {
  Matrix result(mNumRows, mNumCols);

  for (int i = 0; i < mNumRows; i++) {
    for (int j = 0; j < mNumCols; j++) {
      result.mData[i][j] = mData[i][j] - scalar;
    }
  }

  return result;
}

Matrix Matrix::operator*(float scalar) const {
  Matrix result(mNumRows, mNumCols);

  for (int i = 0; i < mNumRows; i++) {
    for (int j = 0; j < mNumCols; j++) {
      result.mData[i][j] = mData[i][j] * scalar;
    }
  }

  return result;
}

Matrix Matrix::transpose() const {
  Matrix result(mNumCols, mNumRows);

  for (int i = 0; i < mNumRows; i++) {
    for (int j = 0; j < mNumCols; j++) {
      result.mData[j][i] = mData[i][j];
    }
  }

  return result;
}

float Matrix::determinant() const {
  assert(mNumRows == mNumCols);

  int n = mNumRows;
  Matrix temp(*this);

  float det = 1.0f;
  int sign = 1;

  for (int i = 0; i < n; i++) {
    int pivotRow = i;
    float maxValue = std::fabs(temp.mData[i][i]);

    for (int r = i + 1; r < n; r++) {
      float value = std::fabs(temp.mData[r][i]);

      if (value > maxValue) {
        maxValue = value;
        pivotRow = r;
      }
    }

    if (maxValue < 1e-7f) {
      return 0.0f;
    }

    if (pivotRow != i) {
      float *tempRow = temp.mData[i];
      temp.mData[i] = temp.mData[pivotRow];
      temp.mData[pivotRow] = tempRow;

      sign *= -1;
    }

    float pivot = temp.mData[i][i];
    det *= pivot;

    for (int r = i + 1; r < n; r++) {
      float factor = temp.mData[r][i] / pivot;

      for (int c = i; c < n; c++) {
        temp.mData[r][c] -= factor * temp.mData[i][c];
      }
    }
  }

  return det * sign;
}

Matrix Matrix::inverse() const {
  assert(mNumRows == mNumCols);

  int n = mNumRows;
  int width = 2 * n;

  float **augmented = new float *[n];

  for (int i = 0; i < n; i++) {
    augmented[i] = new float[width];

    for (int j = 0; j < n; j++) {
      augmented[i][j] = mData[i][j];
    }

    for (int j = n; j < width; j++) {
      augmented[i][j] = 0.0f;
    }

    augmented[i][n + i] = 1.0f;
  }

  for (int i = 0; i < n; i++) {
    int pivotRow = i;
    float maxValue = std::fabs(augmented[i][i]);

    for (int r = i + 1; r < n; r++) {
      float value = std::fabs(augmented[r][i]);

      if (value > maxValue) {
        maxValue = value;
        pivotRow = r;
      }
    }

    assert(maxValue > 1e-7f);

    if (pivotRow != i) {
      float *tempRow = augmented[i];
      augmented[i] = augmented[pivotRow];
      augmented[pivotRow] = tempRow;
    }

    float pivot = augmented[i][i];

    for (int c = 0; c < width; c++) {
      augmented[i][c] /= pivot;
    }

    for (int r = 0; r < n; r++) {
      if (r != i) {
        float factor = augmented[r][i];

        for (int c = 0; c < width; c++) {
          augmented[r][c] -= factor * augmented[i][c];
        }
      }
    }
  }

  Matrix result(n, n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result.mData[i][j] = augmented[i][j + n];
    }
  }

  for (int i = 0; i < n; i++) {
    delete[] augmented[i];
  }
  delete[] augmented;

  return result;
}

Matrix Matrix::pseudoInverse() const {
  Matrix transposed = transpose();

  if (mNumRows >= mNumCols) {
    Matrix left = transposed * (*this);
    return left.inverse() * transposed;
  }

  Matrix right = (*this) * transposed;
  return transposed * right.inverse();
}

void Matrix::print() const {
  for (int i = 0; i < mNumRows; i++) {
    for (int j = 0; j < mNumCols; j++) {
      std::cout << mData[i][j] << " ";
    }

    std::cout << std::endl;
  }
}

Matrix operator+(float scalar, const Matrix &A) {
  return A + scalar;
}

Matrix operator-(float scalar, const Matrix &A) {
  Matrix result(A.mNumRows, A.mNumCols);

  for (int i = 0; i < A.mNumRows; i++) {
    for (int j = 0; j < A.mNumCols; j++) {
      result.mData[i][j] = scalar - A.mData[i][j];
    }
  }

  return result;
}

Matrix operator*(float scalar, const Matrix &A) {
  return A * scalar;
}
