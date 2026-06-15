#include <iostream>
#include <string>
#include "Vector/Vector.hpp"
#include "Matrix/Matrix.hpp"
#include "LinearSystem/LinearSystem.hpp"
#include "LinearSystem/PosSymLinSystem.hpp"
#include "LinearSystem/SolverHelpers.hpp"
#include "Regression/Regression.hpp"

static void testVector() {
    std::cout << "=== Vector test ===" << std::endl;

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
    (v1 * 2.0).print();

    std::cout << "dot(v1, v2): " << (v1 * v2) << std::endl;
}

static void testMatrix() {
    std::cout << "\n=== Matrix test ===" << std::endl;

    Matrix A(2, 2);
    A(1, 1) = 1;
    A(1, 2) = 2;
    A(2, 1) = 3;
    A(2, 2) = 4;

    std::cout << "A:" << std::endl;
    A.print();

    std::cout << "det(A): " << A.determinant() << std::endl;

    Matrix invA = A.inverse();
    std::cout << "inverse(A):" << std::endl;
    invA.print();

    std::cout << "A * inverse(A):" << std::endl;
    (A * invA).print();

    Vector v(2);
    v(1) = 5;
    v(2) = 6;

    std::cout << "A * v: ";
    (A * v).print();
}

static void testLinearSystem() {
    std::cout << "\n=== LinearSystem test ===" << std::endl;

    Matrix A(3, 3);
    A(1, 1) = 2;
    A(1, 2) = 1;
    A(1, 3) = -1;
    A(2, 1) = -3;
    A(2, 2) = -1;
    A(2, 3) = 2;
    A(3, 1) = -2;
    A(3, 2) = 1;
    A(3, 3) = 2;

    Vector b(3);
    b(1) = 8;
    b(2) = -11;
    b(3) = -3;

    LinearSystem system(A, b);
    Vector x = system.Solve();

    std::cout << "Solution of Ax=b: ";
    x.print();
}

static void testPositiveSymmetricSystem() {
    std::cout << "\n=== PosSymLinSystem test ===" << std::endl;

    Matrix A(2, 2);
    A(1, 1) = 4;
    A(1, 2) = 1;
    A(2, 1) = 1;
    A(2, 2) = 3;

    Vector b(2);
    b(1) = 1;
    b(2) = 2;

    PosSymLinSystem system(A, b);
    Vector x = system.Solve();

    std::cout << "CG solution: ";
    x.print();
}

static void testNonSquareSystem() {
    std::cout << "\n=== Non-square system test ===" << std::endl;

    Matrix A(3, 2);
    A(1, 1) = 1;
    A(1, 2) = 1;
    A(2, 1) = 1;
    A(2, 2) = 2;
    A(3, 1) = 1;
    A(3, 2) = 3;

    Vector b(3);
    b(1) = 6;
    b(2) = 5;
    b(3) = 7;

    Vector x = solveByTikhonov(A, b, 1e-8);

    std::cout << "Least-squares/Tikhonov solution: ";
    x.print();
}

static void runRegressionIfRequested(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "\nTo run CPU regression: ./main path/to/machine.data" << std::endl;
        return;
    }

    std::cout << "\n=== CPU regression test ===" << std::endl;

    RegressionResult result = runCpuRegression(argv[1]);

    std::cout << "Parameters x1..x6: ";
    result.parameters.print();
    std::cout << "RMSE: " << result.rmse << std::endl;
}

int main(int argc, char** argv) {
    testVector();
    testMatrix();
    testLinearSystem();
    testPositiveSymmetricSystem();
    testNonSquareSystem();
    runRegressionIfRequested(argc, argv);

    return 0;
}
