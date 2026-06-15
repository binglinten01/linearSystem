#include "PosSymLinSystem.hpp"
#include <cassert>
#include <cmath>

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b) {
    for (int i = 1; i <= mSize; i++) {
        for (int j = 1; j <= mSize; j++) {
            assert(std::fabs((*mpA)(i, j) - (*mpA)(j, i)) < 1e-10);
        }
    }
}

Vector PosSymLinSystem::Solve() const {
    Vector x(mSize);
    Vector r = (*mpb) - ((*mpA) * x);
    Vector p = r;

    double rsOld = r * r;

    if (std::sqrt(rsOld) < 1e-10) {
        return x;
    }

    int maxIterations = mSize * 100;

    for (int iter = 0; iter < maxIterations; iter++) {
        Vector Ap = (*mpA) * p;
        double denominator = p * Ap;

        assert(std::fabs(denominator) > 1e-14);

        double alpha = rsOld / denominator;

        x += p * alpha;
        r -= Ap * alpha;

        double rsNew = r * r;

        if (std::sqrt(rsNew) < 1e-10) {
            break;
        }

        p = r + p * (rsNew / rsOld);
        rsOld = rsNew;
    }

    return x;
}
