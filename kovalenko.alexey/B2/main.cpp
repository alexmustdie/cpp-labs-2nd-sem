#include <iostream>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <cstring>
#include "TextHandler.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc == 2 || argc > 3)
    {
      throw std::invalid_argument("Invalid number of arguments");
    }

    size_t line_width = 40;

    if (argc == 3)
    {
      if (strcmp(argv[1], "--line-width") != 0)
      {
        throw std::invalid_argument("Invalid arguments");
      }
      
      line_width = atoi(argv[2]);
      
      if (line_width < 24)
      {
        throw std::invalid_argument("Invalid line width");
      }
    }

    TextHandler<std::vector<char>::iterator> text_handler(line_width);
    
    std::vector<char> vector;
    std::cin >> std::noskipws;
    
    std::copy(std::istream_iterator<char>(std::cin), std::istream_iterator<char>(), std::back_inserter(vector));
    
    if (!std::cin.eof())
    {
      throw std::ios_base::failure("Error while reading the file");
    }

    text_handler.handle(vector.begin(), vector.end());
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
