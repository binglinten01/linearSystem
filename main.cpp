#include <iostream>
#include "Vector.hpp"

int main() {
  Vector v1(3);
  v1(1) = 10;
  v1(2) = 5;
  v1(3) = 12;

  Vector v2(3);
  v2(1) = 5;
  v2(2) = 2;
  v2(3) = 1;

  v1.print();
  v2.print();

  (v1 + v2).print();

  return 0;
}
