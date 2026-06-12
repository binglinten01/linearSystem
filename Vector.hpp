#ifndef Vector_HPP
#define Vector_HPP

class Vector {
  int mSize;
  float* mData;

  public:
    Vector(int size);
    ~Vector();

    void print();
    float& operator()(int index);
    Vector operator+(Vector& other);
    Vector operator-(Vector& other);
};

#endif
