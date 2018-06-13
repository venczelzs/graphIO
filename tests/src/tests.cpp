// tests/tests.cpp

#include <iostream>

#include "matrix.hpp"

using namespace Matrica;

int main() {
  std::cout << "Let's do some tests" << std::endl;

  Matrix<uint> id = Matrices::Identity(3);

  std::cout << "Testing matrix relation operators" << std::endl;
  
  if (!(id == id)) {
    std::cout << "(==) not ok" << std::endl;
    return 1;
  }
  else {
    std::cout << "(==) all right" << std::endl;
  }
  
  return 0;
};
