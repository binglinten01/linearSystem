#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../Vector/Vector.hpp"

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    float** mData;

public:
    Matrix(int numRows, int numCols);
    Matrix(const Matrix& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);

    int getNumRows() const;
    int getNumCols() const;

    float& operator()(int i, int j);
    const float& operator()(int i, int j) const;

    Matrix operator+() const;
    Matrix operator-() const;

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Vector operator*(const Vector& v) const;

    Matrix operator+(float scalar) const;
    Matrix operator-(float scalar) const;
    Matrix operator*(float scalar) const;

    Matrix transpose() const;
    float determinant() const;
    Matrix inverse() const;
    Matrix pseudoInverse() const;

    void print() const;
};

#endif
