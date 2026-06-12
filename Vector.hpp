#ifndef Vector_HPP
#define Vector_HPP

class Vector {
  int mSize;
  float* mData;

  public:
    Vector(int size);
    ~Vector();

    float& operator()(int index);
};

#endif
