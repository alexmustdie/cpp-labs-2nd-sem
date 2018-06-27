#include <iostream>
#include <stdexcept>
#include <list>
#include "tasks.hpp"

void secondTask()
{
  std::list<size_t> list = {};
  size_t n = 0;

  while (std::cin && !(std::cin >> n).eof())
  {
    if (std::cin.fail() || std::cin.bad())
    {
      throw std::ios_base::failure("Error while reading data");
    }
    
    if (n < 1 || n > 20)
    {
      throw std::invalid_argument("Number must be from 1 to 20");
    }

    list.push_back(n);
  }

  if (list.size() > 20)
  {
    throw std::invalid_argument("List can contain up to 20 numbers");
  }

  for (auto i = list.begin(), j = list.end(); i != j--; i++)
  {
    if (i == j)
    {
      std::cout << *i << "\n";
      return;
    }
   
    std::cout << *i << " " << *j << " ";
  }

  std::cout << "\n";
  return;
}
