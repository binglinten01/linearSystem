#include "Matrix.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

Matrix::Matrix(int numRows, int numCols) {
    assert(numRows > 0);
    assert(numCols > 0);

    mNumRows = numRows;
    mNumCols = numCols;

    mData = new double*[mNumRows];

    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols];

        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(const Matrix& other) {
    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;

    mData = new double*[mNumRows];

    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols];

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

    mData = new double*[mNumRows];

    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols];

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

double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);

    return mData[i - 1][j - 1];
}

const double& Matrix::operator()(int i, int j) const {
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
            double sum = 0.0;

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
        double sum = 0.0;

        for (int j = 1; j <= mNumCols; j++) {
            sum += (*this)(i, j) * v(j);
        }

        result(i) = sum;
    }

    return result;
}

Matrix Matrix::operator+(double scalar) const {
    Matrix result(mNumRows, mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] + scalar;
        }
    }

    return result;
}

Matrix Matrix::operator-(double scalar) const {
    Matrix result(mNumRows, mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] - scalar;
        }
    }

    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] * scalar;
        }
    }

    return result;
}

Matrix Matrix::operator/(double scalar) const {
    assert(std::fabs(scalar) > 1e-14);

    Matrix result(mNumRows, mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] / scalar;
        }
    }

    return result;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    assert(mNumRows == other.mNumRows);
    assert(mNumCols == other.mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] += other.mData[i][j];
        }
    }

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    assert(mNumRows == other.mNumRows);
    assert(mNumCols == other.mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] -= other.mData[i][j];
        }
    }

    return *this;
}

Matrix& Matrix::operator*=(double scalar) {
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] *= scalar;
        }
    }

    return *this;
}

Matrix& Matrix::operator/=(double scalar) {
    assert(std::fabs(scalar) > 1e-14);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] /= scalar;
        }
    }

    return *this;
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

Matrix Matrix::identity(int size) {
    assert(size > 0);

    Matrix result(size, size);

    for (int i = 1; i <= size; i++) {
        result(i, i) = 1.0;
    }

    return result;
}

double Matrix::determinant() const {
    assert(mNumRows == mNumCols);

    int n = mNumRows;
    Matrix temp(*this);

    double det = 1.0;
    int sign = 1;

    for (int i = 0; i < n; i++) {
        int pivotRow = i;
        double maxValue = std::fabs(temp.mData[i][i]);

        for (int r = i + 1; r < n; r++) {
            double value = std::fabs(temp.mData[r][i]);

            if (value > maxValue) {
                maxValue = value;
                pivotRow = r;
            }
        }

        if (maxValue < 1e-12) {
            return 0.0;
        }

        if (pivotRow != i) {
            double* row = temp.mData[i];
            temp.mData[i] = temp.mData[pivotRow];
            temp.mData[pivotRow] = row;
            sign *= -1;
        }

        double pivot = temp.mData[i][i];
        det *= pivot;

        for (int r = i + 1; r < n; r++) {
            double factor = temp.mData[r][i] / pivot;

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

    double** augmented = new double*[n];

    for (int i = 0; i < n; i++) {
        augmented[i] = new double[width];

        for (int j = 0; j < n; j++) {
            augmented[i][j] = mData[i][j];
        }

        for (int j = n; j < width; j++) {
            augmented[i][j] = 0.0;
        }

        augmented[i][n + i] = 1.0;
    }

    for (int i = 0; i < n; i++) {
        int pivotRow = i;
        double maxValue = std::fabs(augmented[i][i]);

        for (int r = i + 1; r < n; r++) {
            double value = std::fabs(augmented[r][i]);

            if (value > maxValue) {
                maxValue = value;
                pivotRow = r;
            }
        }

        assert(maxValue > 1e-12);

        if (pivotRow != i) {
            double* row = augmented[i];
            augmented[i] = augmented[pivotRow];
            augmented[pivotRow] = row;
        }

        double pivot = augmented[i][i];

        for (int c = 0; c < width; c++) {
            augmented[i][c] /= pivot;
        }

        for (int r = 0; r < n; r++) {
            if (r != i) {
                double factor = augmented[r][i];

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
        Matrix normalLeft = transposed * (*this);
        return normalLeft.inverse() * transposed;
    }

    Matrix normalRight = (*this) * transposed;
    return transposed * normalRight.inverse();
}

void Matrix::print() const {
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            std::cout << mData[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

Matrix operator+(double scalar, const Matrix& A) {
    return A + scalar;
}

Matrix operator-(double scalar, const Matrix& A) {
    Matrix result(A.mNumRows, A.mNumCols);

    for (int i = 0; i < A.mNumRows; i++) {
        for (int j = 0; j < A.mNumCols; j++) {
            result.mData[i][j] = scalar - A.mData[i][j];
        }
    }

    return result;
}

Matrix operator*(double scalar, const Matrix& A) {
    return A * scalar;
}
