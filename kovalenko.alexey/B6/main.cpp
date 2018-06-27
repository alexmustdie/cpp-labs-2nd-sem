#include <iostream>
#include <string>
#include "part.hpp"

int main(int args, char *argv[])
{

  if(args != 2)
  {
    std::cerr << "Invalid number of arguments";
    return 1;
  }

  try
  {
    int option = std::stoi(argv[1]);
    switch(option)
    {
    case 1:
      optionOne(std::cin, std::cout);
      break;
    case 2:
      optionTwo(std::cin, std::cout);
      break;
    default:
      std::cerr << "invalid option";
      return 1;
    }
  }
  catch(const std::invalid_argument &e)
  {
    std::cerr << e.what();
    return 1;
  }
  
  return 0;
}

