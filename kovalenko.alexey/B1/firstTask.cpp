#include <memory>
#include <stdexcept>
#include <vector>
#include <forward_list>
#include "tasks.hpp"
#include "funcs.hpp"
#include "Access.hpp"

void firstTask(char* direction)
{
  bool reverse = isReverse(direction);

  using Vector = std::vector<int>;
  using List = std::forward_list<int>;

  Vector vector_1 = {};
  
  int n = 0;
  size_t size = 0;

  while (std::cin && !(std::cin >> n).eof())
  {
    if (std::cin.fail() || std::cin.bad())
    {
      throw std::ios_base::failure("Error while reading the file");
    }

    vector_1.push_back(n);
    size++;
  }

  if (vector_1.empty())
  {
    return;
  }

  Vector vector_2(vector_1.begin(), vector_1.end());
  List vector_3(vector_1.begin(), vector_1.end());
  
  sort<Vector, Access<Vector>::Bracket>(vector_1, size, reverse);
  sort<Vector, Access<Vector>::At>(vector_2, size, reverse);
  sort<List, Access<List>::Iter>(vector_3, size, reverse);

  print(vector_1);
  std::cout << "\n";
  
  print(vector_2);
  std::cout << "\n";
  
  print(vector_3);
}
