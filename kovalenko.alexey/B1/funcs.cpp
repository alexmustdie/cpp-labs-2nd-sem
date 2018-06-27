#include <stdexcept>
#include <cstring>
#include "funcs.hpp"

bool isReverse(char* direction)
{
  bool reverse = false;

  if (strcmp(direction, "descending") == 0)
  {
    reverse = true;
  }
  else
  {
    if (strcmp(direction, "ascending") != 0)
    {
      throw std::invalid_argument("Invalid direction");
    }
  }

  return reverse;
}
