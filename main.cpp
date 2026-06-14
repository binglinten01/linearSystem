#include "Matrix/Matrix.hpp"
#include "Vector/Vector.hpp"
#include <iostream>

int main() {
  Matrix A(2, 2);

  A(1, 1) = 1;
  A(1, 2) = 2;
  A(2, 1) = 3;
  A(2, 2) = 4;

  std::cout << "A:" << std::endl;
  A.print();

  std::cout << "det(A): " << A.determinant() << std::endl;

  std::cout << "inverse(A):" << std::endl;
  Matrix invA = A.inverse();
  invA.print();

  std::cout << "A * inverse(A):" << std::endl;
  Matrix identity = A * invA;
  identity.print();

  Vector v(2);
  v(1) = 5;
  v(2) = 6;

  std::cout << "A * v:" << std::endl;
  Vector result = A * v;
  result.print();

  return 0;
}
