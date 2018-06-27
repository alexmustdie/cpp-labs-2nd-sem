#include <stdexcept>
#include <vector>
#include <cmath>
#include "tasks.hpp"
#include "funcs.hpp"
#include "Access.hpp"

void fillRandom(double* array, int size)
{
  double n = 0;
  srand(time(NULL));

  for (int i = 0; i < size; i++)
  {
    n = 2 * (static_cast<double>(rand()) / RAND_MAX) - 1;
    array[i] = floor(n * 10) / 10;
  }
}

void fourthTask(char* direction, char* size)
{
  bool reverse = isReverse(direction);
  int vector_size = atoi(size);

  if (vector_size <= 0)
  {
    throw std::invalid_argument("The size must be greater than zero");
  }

  using Vector = std::vector<double>;

  Vector vector(vector_size);

  fillRandom(vector.data(), vector_size);
  print(vector);

  std::cout << "\n";

  sort<Vector, Access<Vector>::Bracket>(vector, vector_size, reverse);
  print(vector);
}
