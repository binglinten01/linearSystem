#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
private:
    int mSize;
    float* mData;

public:
    Vector(int size);
    Vector(const Vector& other);
    ~Vector();

    Vector& operator=(const Vector& other);

    int getSize() const;

    float& operator[](int index);
    const float& operator[](int index) const;

    float& operator()(int index);
    const float& operator()(int index) const;

    Vector operator+() const;
    Vector operator-() const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    Vector operator+(float scalar) const;
    Vector operator-(float scalar) const;
    Vector operator*(float scalar) const;

    float operator*(const Vector& other) const;

    void print() const;
};

#endif
