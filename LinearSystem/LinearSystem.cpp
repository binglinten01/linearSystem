#include "LinearSystem.hpp"
#include <cassert>
#include <cmath>

LinearSystem::LinearSystem(const Matrix& A, const Vector& b) {
    assert(A.getNumRows() == A.getNumCols());
    assert(A.getNumRows() == b.getSize());

    mSize = A.getNumRows();
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystem::LinearSystem(const LinearSystem& other) {
    mSize = other.mSize;
    mpA = new Matrix(*(other.mpA));
    mpb = new Vector(*(other.mpb));
}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

LinearSystem& LinearSystem::operator=(const LinearSystem& other) {
    if (this == &other) {
        return *this;
    }

    delete mpA;
    delete mpb;

    mSize = other.mSize;
    mpA = new Matrix(*(other.mpA));
    mpb = new Vector(*(other.mpb));

    return *this;
}

Vector LinearSystem::Solve() const {
    Matrix A(*mpA);
    Vector b(*mpb);

    for (int k = 1; k <= mSize - 1; k++) {
        int pivotRow = k;
        float largest = std::fabs(A(k, k));

        for (int i = k + 1; i <= mSize; i++) {
            if (std::fabs(A(i, k)) > largest) {
                largest = std::fabs(A(i, k));
                pivotRow = i;
            }
        }

        assert(largest > 1e-7f);

        if (pivotRow != k) {
            for (int j = k; j <= mSize; j++) {
                float temp = A(k, j);
                A(k, j) = A(pivotRow, j);
                A(pivotRow, j) = temp;
            }

            float temp = b(k);
            b(k) = b(pivotRow);
            b(pivotRow) = temp;
        }

        for (int i = k + 1; i <= mSize; i++) {
            float factor = A(i, k) / A(k, k);

            for (int j = k; j <= mSize; j++) {
                A(i, j) = A(i, j) - factor * A(k, j);
            }

            b(i) = b(i) - factor * b(k);
        }
    }

    Vector x(mSize);

    for (int i = mSize; i >= 1; i--) {
        float sum = b(i);

        for (int j = i + 1; j <= mSize; j++) {
            sum = sum - A(i, j) * x(j);
        }

        assert(std::fabs(A(i, i)) > 1e-7f);
        x(i) = sum / A(i, i);
    }

    return x;
}
