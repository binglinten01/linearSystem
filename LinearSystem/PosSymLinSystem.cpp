#include "PosSymLinSystem.hpp"
#include <cassert>
#include <cmath>

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b) {
    for (int i = 1; i <= mSize; i++) {
        for (int j = 1; j <= mSize; j++) {
            assert(std::fabs((*mpA)(i, j) - (*mpA)(j, i)) < 1e-5f);
        }
    }
}

Vector PosSymLinSystem::Solve() const {
    Vector x(mSize);
    Vector r(*mpb);
    Vector p(r);

    float oldResidual = r * r;

    for (int iteration = 0; iteration < 1000; iteration++) {
        Vector Ap = (*mpA) * p;
        float alpha = oldResidual / (p * Ap);

        x = x + p * alpha;
        r = r - Ap * alpha;

        float newResidual = r * r;

        if (std::sqrt(newResidual) < 1e-5f) {
            break;
        }

        p = r + p * (newResidual / oldResidual);
        oldResidual = newResidual;
    }

    return x;
}
