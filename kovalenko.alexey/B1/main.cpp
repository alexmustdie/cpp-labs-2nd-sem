#include <iostream>
#include <memory>
#include <stdexcept>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc > 1)
    {
      size_t task_number = atoi(argv[1]);

      switch (task_number)
      {
        case 1:
          if (argc == 3)
          {
            firstTask(argv[2]);
          }
          else
          {
            throw std::invalid_argument("No direction specifed");
          }
          break;
        case 2:
          if (argc == 3)
          {
            secondTask(argv[2]);
          }
          else
          {
            throw std::invalid_argument("No filename specifed");
          }
          break;
        case 3:
          thirdTask();
          break;
        case 4:
          if (argc == 4)
          {
            fourthTask(argv[2], argv[3]);
          }
          else
          {
            throw std::invalid_argument("No direction or size specifed");
          }
          break;
        default:
          throw std::invalid_argument("Invalid task number");
          break;
      }
    }
    else
    {
      throw std::invalid_argument("No task number specifed");
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::ios_base::failure& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown exception\n";
    return 1;
  }

  return 0;
}
