#include <iostream>

#include "add.h"

int main(int argc, char** argv) {
  std::cout << nitr::case001::add(3, 4) << "\n";
  std::cout << nitr::case001::add(3.5, 4.5) << "\n";
  std::cout << nitr::case001::add(100000000.0, 1.0) << "\n";
  std::cout << nitr::case001::add(100000000, 100000000) << "\n";
  return 0;
}
