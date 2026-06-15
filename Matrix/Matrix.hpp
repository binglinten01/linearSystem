#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../Vector/Vector.hpp"

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;

public:
    Matrix(int numRows, int numCols);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);

    int getNumRows() const;
    int getNumCols() const;

    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    Matrix operator+() const;
    Matrix operator-() const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Vector operator*(const Vector& v) const;

    Matrix operator+(double scalar) const;
    Matrix operator-(double scalar) const;
    Matrix operator*(double scalar) const;
    Matrix operator/(double scalar) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(double scalar);
    Matrix& operator/=(double scalar);

    Matrix transpose() const;
    static Matrix identity(int size);

    double determinant() const;
    Matrix inverse() const;
    Matrix pseudoInverse() const;

    void print() const;

    friend Matrix operator+(double scalar, const Matrix& A);
    friend Matrix operator-(double scalar, const Matrix& A);
    friend Matrix operator*(double scalar, const Matrix& A);
};

#endif
