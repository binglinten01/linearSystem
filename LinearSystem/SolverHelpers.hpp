#ifndef SOLVER_HELPERS_HPP
#define SOLVER_HELPERS_HPP

#include "../Matrix/Matrix.hpp"
#include "../Vector/Vector.hpp"

Vector solveByPseudoInverse(const Matrix& A, const Vector& b);
Vector solveByTikhonov(const Matrix& A, const Vector& b, double lambda);

#endif
