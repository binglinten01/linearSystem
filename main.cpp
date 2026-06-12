#include <iostream>
#include "Vector.hpp"

int main() {
  Vector v(3);

  v(1) = 10;

  std::cout << v(1) << std::endl;

  return 0;
}
