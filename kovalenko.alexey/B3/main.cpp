#include <iostream>
#include <stdexcept>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc == 2)
    {
      size_t task_number = atoi(argv[1]);

      switch (task_number)
      {
        case 1:
          firstTask();
          break;
        case 2:
          secondTask();
          break;
        default:
          throw std::invalid_argument("Invalid task number");
      }
    }
    else
    {
      throw std::invalid_argument("No task number specifed");
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unhandled exception\n";
    return 1;
  }

  return 0;
}
