#ifndef MISSIONFACTORIAL
#define MISSIONFACTORIAL

#include <algorithm>
#include <iostream>
#include "factorialContainer.hpp"

void printFactorial()
{
  Container container;

  std::copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << std::endl;

  std::reverse_copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << std::endl;
}

#endif
