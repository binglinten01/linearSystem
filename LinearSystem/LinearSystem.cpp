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

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

Vector LinearSystem::Solve() const {
    Matrix A(*mpA);
    Vector b(*mpb);

    for (int k = 1; k <= mSize - 1; k++) {
        int pivotRow = k;
        double maxValue = std::fabs(A(k, k));

        for (int r = k + 1; r <= mSize; r++) {
            double value = std::fabs(A(r, k));

            if (value > maxValue) {
                maxValue = value;
                pivotRow = r;
            }
        }

        assert(maxValue > 1e-12);

        if (pivotRow != k) {
            for (int c = k; c <= mSize; c++) {
                double temp = A(k, c);
                A(k, c) = A(pivotRow, c);
                A(pivotRow, c) = temp;
            }

            double tempB = b(k);
            b(k) = b(pivotRow);
            b(pivotRow) = tempB;
        }

        for (int r = k + 1; r <= mSize; r++) {
            double factor = A(r, k) / A(k, k);
            A(r, k) = 0.0;

            for (int c = k + 1; c <= mSize; c++) {
                A(r, c) -= factor * A(k, c);
            }

            b(r) -= factor * b(k);
        }
    }

    assert(std::fabs(A(mSize, mSize)) > 1e-12);

    Vector x(mSize);

    for (int i = mSize; i >= 1; i--) {
        double sum = b(i);

        for (int j = i + 1; j <= mSize; j++) {
            sum -= A(i, j) * x(j);
        }

        assert(std::fabs(A(i, i)) > 1e-12);
        x(i) = sum / A(i, i);
    }

    return x;
}
