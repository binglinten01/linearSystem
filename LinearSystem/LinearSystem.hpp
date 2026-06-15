#ifndef LINEAR_SYSTEM_HPP
#define LINEAR_SYSTEM_HPP

#include "../Matrix/Matrix.hpp"
#include "../Vector/Vector.hpp"

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

public:
    LinearSystem(const Matrix& A, const Vector& b);
    LinearSystem(const LinearSystem& other);
    virtual ~LinearSystem();

    LinearSystem& operator=(const LinearSystem& other);

    virtual Vector Solve() const;
};

#endif
