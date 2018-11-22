#include <memory>
#include <stdexcept>
#include <vector>
#include "tasks.hpp"
#include "funcs.hpp"

void thirdTask()
{
  std::vector<int> vector = {};

  int n = 0;
  size_t multiple = 0;

  while (std::cin && !(std::cin >> n).eof())
  {
    if (std::cin.fail() || std::cin.bad())
    {
      throw std::ios_base::failure("Error while reading data");
    }

    if (n == 0)
    {
      break;
    }

    if (n % 3 == 0)
    {
      multiple++;
    }

    vector.push_back(n);
  }

  if (vector.empty())
  {
    return;
  }

  if (n != 0)
  {
    throw std::invalid_argument("Missing zero");
  }

  switch (vector.back())
  {
    case 1:
    
      for (auto it = vector.begin(); it != vector.end(); ++it)
      {
        if (*it % 2 == 0)
        {
          vector.erase(it);
          it--;
        }
      }

      break;

    case 2:

      vector.reserve(vector.size() + multiple * 3);

      for (auto it = vector.begin(); it != vector.end(); ++it)
      { 
        if (*it % 3 == 0)
        {
          vector.insert(it + 1, 3, 1);
          it += 2;
        }
      }

      break; 
  }

  print(vector);
}
