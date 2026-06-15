#include "SolverHelpers.hpp"
#include <cassert>

Vector solveByPseudoInverse(const Matrix& A, const Vector& b) {
    assert(A.getNumRows() == b.getSize());
    return A.pseudoInverse() * b;
}

Vector solveByTikhonov(const Matrix& A, const Vector& b, double lambda) {
    assert(A.getNumRows() == b.getSize());
    assert(lambda >= 0.0);

    Matrix At = A.transpose();
    Matrix normal = At * A;

    for (int i = 1; i <= normal.getNumRows(); i++) {
        normal(i, i) += lambda;
    }

    Vector rightSide = At * b;

    return normal.inverse() * rightSide;
}
