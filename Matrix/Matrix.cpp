#include "Matrix.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

Matrix::Matrix(int numRows, int numCols) {
    assert(numRows > 0);
    assert(numCols > 0);

    mNumRows = numRows;
    mNumCols = numCols;

    mData = new float*[mNumRows];

    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new float[mNumCols];

        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = 0.0f;
        }
    }
}

Matrix::Matrix(const Matrix& other) {
    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;

    mData = new float*[mNumRows];

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

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < mNumRows; i++) {
        delete[] mData[i];
    }
    delete[] mData;

    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;

    mData = new float*[mNumRows];

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

float& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);

    return mData[i - 1][j - 1];
}

const float& Matrix::operator()(int i, int j) const {
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

Matrix Matrix::operator+(const Matrix& other) const {
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

Matrix Matrix::operator-(const Matrix& other) const {
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

Matrix Matrix::operator*(const Matrix& other) const {
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

Vector Matrix::operator*(const Vector& v) const {
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

    for (int i = 1; i <= mNumRows; i++) {
        for (int j = 1; j <= mNumCols; j++) {
            result(j, i) = (*this)(i, j);
        }
    }

    return result;
}

float Matrix::determinant() const {
    assert(mNumRows == mNumCols);

    Matrix temp(*this);
    int n = mNumRows;
    float det = 1.0f;
    int sign = 1;

    for (int k = 0; k < n; k++) {
        int pivotRow = k;
        float largest = std::fabs(temp.mData[k][k]);

        for (int i = k + 1; i < n; i++) {
            if (std::fabs(temp.mData[i][k]) > largest) {
                largest = std::fabs(temp.mData[i][k]);
                pivotRow = i;
            }
        }

        if (largest < 1e-7f) {
            return 0.0f;
        }

        if (pivotRow != k) {
            float* row = temp.mData[k];
            temp.mData[k] = temp.mData[pivotRow];
            temp.mData[pivotRow] = row;
            sign = -sign;
        }

        float pivot = temp.mData[k][k];
        det *= pivot;

        for (int i = k + 1; i < n; i++) {
            float factor = temp.mData[i][k] / pivot;

            for (int j = k; j < n; j++) {
                temp.mData[i][j] -= factor * temp.mData[k][j];
            }
        }
    }

    return det * sign;
}

Matrix Matrix::inverse() const {
    assert(mNumRows == mNumCols);

    int n = mNumRows;
    Matrix left(*this);
    Matrix right(n, n);

    for (int i = 1; i <= n; i++) {
        right(i, i) = 1.0f;
    }

    for (int k = 1; k <= n; k++) {
        int pivotRow = k;
        float largest = std::fabs(left(k, k));

        for (int i = k + 1; i <= n; i++) {
            if (std::fabs(left(i, k)) > largest) {
                largest = std::fabs(left(i, k));
                pivotRow = i;
            }
        }

        assert(largest > 1e-7f);

        if (pivotRow != k) {
            for (int j = 1; j <= n; j++) {
                float temp = left(k, j);
                left(k, j) = left(pivotRow, j);
                left(pivotRow, j) = temp;

                temp = right(k, j);
                right(k, j) = right(pivotRow, j);
                right(pivotRow, j) = temp;
            }
        }

        float pivot = left(k, k);

        for (int j = 1; j <= n; j++) {
            left(k, j) = left(k, j) / pivot;
            right(k, j) = right(k, j) / pivot;
        }

        for (int i = 1; i <= n; i++) {
            if (i != k) {
                float factor = left(i, k);

                for (int j = 1; j <= n; j++) {
                    left(i, j) = left(i, j) - factor * left(k, j);
                    right(i, j) = right(i, j) - factor * right(k, j);
                }
            }
        }
    }

    return right;
}

Matrix Matrix::pseudoInverse() const {
    Matrix transposed = transpose();

    if (mNumRows >= mNumCols) {
        Matrix normal = transposed * (*this);
        return normal.inverse() * transposed;
    }

    Matrix normal = (*this) * transposed;
    return transposed * normal.inverse();
}

void Matrix::print() const {
    for (int i = 1; i <= mNumRows; i++) {
        for (int j = 1; j <= mNumCols; j++) {
            std::cout << (*this)(i, j) << " ";
        }

        std::cout << std::endl;
    }
}
