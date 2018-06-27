#include <memory>
#include <stdexcept>
#include <fstream>
#include <vector>
#include "tasks.hpp"
#include "funcs.hpp"

void secondTask(char* filename)
{
  FILE* file = fopen(filename, "r");

  if (file == NULL)
  {
    throw std::ios_base::failure("Unsuccessful opening of the file");
  }

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  std::unique_ptr<char[]> array(new char[size]);
  size = fread(array.get(), sizeof(char), size, file);

  if (fclose(file) == 0)
  {
    std::vector<char> vector(array.get(), array.get() + size);
    print(vector, false);
  }
  else
  {
    throw std::ios_base::failure("File is not closed");
  }
}
