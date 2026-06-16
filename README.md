# Project 1: Linear System

## Description

This project is for solving linear systems using C++ classes.

The main classes are:

* `Vector`
* `Matrix`
* `LinearSystem`
* `PosSymLinSystem`

The project also includes a simple linear regression part using the Computer Hardware dataset.

The linear system has the form:

```txt
Ax = b
```

where:

* `A` is a matrix
* `x` is the unknown vector
* `b` is the right-hand side vector

---

## Folder Structure

```txt
linearSystem/
├── Vector/
│   ├── Vector.hpp
│   └── Vector.cpp
├── Matrix/
│   ├── Matrix.hpp
│   └── Matrix.cpp
├── LinearSystem/
│   ├── LinearSystem.hpp
│   ├── LinearSystem.cpp
│   ├── PosSymLinSystem.hpp
│   └── PosSymLinSystem.cpp
├── Regression/
│   ├── Regression.hpp
│   └── Regression.cpp
├── main.cpp
├── Makefile
├── README.md
└── .gitignore
```

---

## Classes

### Vector

The `Vector` class stores a one-dimensional array.

It includes:

* constructor
* copy constructor
* destructor
* assignment operator
* addition and subtraction
* scalar multiplication
* dot product
* `operator()` for one-based indexing
* `operator[]` for zero-based indexing

Example:

```cpp
Vector v(3);

v(1) = 10;
v(2) = 5;
v(3) = 12;

v.print();
```

---

### Matrix

The `Matrix` class stores a two-dimensional array.

It includes:

* constructor
* copy constructor
* destructor
* assignment operator
* matrix addition
* matrix subtraction
* matrix multiplication
* matrix-vector multiplication
* scalar multiplication
* transpose
* determinant
* inverse
* pseudo-inverse

Example:

```cpp
Matrix A(2, 2);

A(1, 1) = 1;
A(1, 2) = 2;
A(2, 1) = 3;
A(2, 2) = 4;

A.print();
```

---

### LinearSystem

The `LinearSystem` class solves a square system:

```txt
Ax = b
```

It uses Gaussian elimination with pivoting.

Example:

```cpp
LinearSystem system(A, b);
Vector x = system.Solve();
```

---

### PosSymLinSystem

`PosSymLinSystem` is derived from `LinearSystem`.

It is used for symmetric positive definite systems.

It solves the system using the conjugate gradient method.

---

## Regression Part

The regression part uses the UCI Computer Hardware dataset.

The model is:

```txt
PRP = x1*MYCT + x2*MMIN + x3*MMAX + x4*CACH + x5*CHMIN + x6*CHMAX
```

The program uses:

* `MYCT`
* `MMIN`
* `MMAX`
* `CACH`
* `CHMIN`
* `CHMAX`

as input values.

It uses `PRP` as the expected output.

The dataset is split into:

```txt
80% training data
20% testing data
```

The error is calculated using RMSE.

---

## Basic Requirements

The project needs:

```txt
g++
make
```

The code is compiled using C++17.

---

## Regression prerequisites

Download the Computer Hardware dataset.

The data file should be named:

```txt
machine.data
```

Put `machine.data` in the `data/` folder.

If no dataset is given, the program will still run the normal tests for `Vector`, `Matrix`, and `LinearSystem`.

---

## Makefile scripts

Build the project:

```bash
make build
```

Run the project:

```bash
make run
```

Clean compiled files:

```bash
make clean
```

Usually, this is enough:

```bash
make run
```

---

## How to run

### Linux / WSL

```bash
make clean
make build
make run
```

### Windows

```bash
g++ -Wall -Wextra -std=c++17 main.cpp Vector/Vector.cpp Matrix/Matrix.cpp LinearSystem/LinearSystem.cpp LinearSystem/PosSymLinSystem.cpp Regression/Regression.cpp -o main.exe
./main.exe
```

---

## Notes

* `operator()` uses one-based indexing, so `v(1)` means the first element.
* Dynamic memory is used for `Vector` and `Matrix`.
* Copy constructors and assignment operators are used to avoid shallow copy problems.
* The pseudo-inverse is used for non-square systems.
* The regression part only works if the dataset file is provided.
