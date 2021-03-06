#include <iostream>
#include <exception>
#include "printFactorial.hpp"
#include "bookInterface.hpp"

int main(int agrc, char *argv[])
{
  if (agrc != 2)
  {
    std::cerr << "incorrect parameters" << std::endl;
    return 1;
  }
  try
  {
    switch (std::atoi(argv[1]))
    {
    case 1:
      bookInterface();
      break;
    case 2:
      printFactorial();
      break;
    default:
      throw std::invalid_argument("Invalid number of items");
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
