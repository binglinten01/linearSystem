#include <iostream>
#include "Vector/Vector.hpp"
#include "Matrix/Matrix.hpp"
#include "LinearSystem/LinearSystem.hpp"
#include "LinearSystem/PosSymLinSystem.hpp"
#include "Regression/Regression.hpp"

int main() {
    std::cout << "Vector test" << std::endl;

    Vector v1(3);
    v1(1) = 10;
    v1(2) = 5;
    v1(3) = 12;

    Vector v2(3);
    v2(1) = 5;
    v2(2) = 2;
    v2(3) = 1;

    std::cout << "v1: ";
    v1.print();

    std::cout << "v2: ";
    v2.print();

    std::cout << "v1 + v2: ";
    (v1 + v2).print();

    std::cout << "v1 - v2: ";
    (v1 - v2).print();

    std::cout << "v1 * 2: ";
    (v1 * 2.0f).print();

    std::cout << "v1 dot v2: " << v1 * v2 << std::endl;

    std::cout << std::endl;
    std::cout << "Matrix test" << std::endl;

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

    Vector b2(2);
    b2(1) = 5;
    b2(2) = 11;

    LinearSystem system2(A, b2);
    Vector solution2 = system2.Solve();

    std::cout << "Solution of A x = b:" << std::endl;
    solution2.print();

    std::cout << std::endl;
    std::cout << "3 by 3 linear system test" << std::endl;

    Matrix B(3, 3);
    B(1, 1) = 2;
    B(1, 2) = 1;
    B(1, 3) = -1;
    B(2, 1) = -3;
    B(2, 2) = -1;
    B(2, 3) = 2;
    B(3, 1) = -2;
    B(3, 2) = 1;
    B(3, 3) = 2;

    Vector b3(3);
    b3(1) = 8;
    b3(2) = -11;
    b3(3) = -3;

    LinearSystem system3(B, b3);
    Vector solution3 = system3.Solve();

    std::cout << "Solution should be 2 3 -1:" << std::endl;
    solution3.print();

    std::cout << std::endl;
    std::cout << "Positive symmetric system test" << std::endl;

    Matrix C(2, 2);
    C(1, 1) = 4;
    C(1, 2) = 1;
    C(2, 1) = 1;
    C(2, 2) = 3;

    Vector b4(2);
    b4(1) = 1;
    b4(2) = 2;

    PosSymLinSystem posSystem(C, b4);
    Vector solution4 = posSystem.Solve();

    std::cout << "Conjugate gradient solution:" << std::endl;
    solution4.print();

    std::cout << std::endl;
    std::cout << "Pseudo-inverse test" << std::endl;

    Matrix D(3, 2);
    D(1, 1) = 1;
    D(1, 2) = 0;
    D(2, 1) = 0;
    D(2, 2) = 1;
    D(3, 1) = 1;
    D(3, 2) = 1;

    std::cout << "D:" << std::endl;
    D.print();

    std::cout << "pseudoInverse(D):" << std::endl;
    Matrix pinvD = D.pseudoInverse();
    pinvD.print();

    std::cout << std::endl;

    runRegression("./data/machine.data");

    return 0;
}
