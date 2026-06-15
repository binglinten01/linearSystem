#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
private:
    int mSize;
    double* mData;

public:
    Vector(int size);
    Vector(const Vector& other);
    ~Vector();

    Vector& operator=(const Vector& other);

    int getSize() const;

    double& operator[](int index);
    const double& operator[](int index) const;

    double& operator()(int index);
    const double& operator()(int index) const;

    Vector operator+() const;
    Vector operator-() const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    Vector operator+(double scalar) const;
    Vector operator-(double scalar) const;
    Vector operator*(double scalar) const;
    Vector operator/(double scalar) const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(double scalar);
    Vector& operator/=(double scalar);

    double operator*(const Vector& other) const;

    double norm() const;
    void print() const;

    friend Vector operator+(double scalar, const Vector& v);
    friend Vector operator-(double scalar, const Vector& v);
    friend Vector operator*(double scalar, const Vector& v);
};

#endif
