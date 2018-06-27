#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include "tasks.hpp"
#include "QueueWithPriority.hpp"

void firstTask()
{
  QueueWithPriority<std::string> queue;

  std::string line = "";

  while (std::getline(std::cin, line))
  {
    try
    {
      std::istringstream iss(line);
      std::string word = "";

      iss >> word;

      if (word == "add")
      {
        iss >> word;
        ElementPriority priority;

        if (word == "low")
        {
          priority = LOW;
        }
        else if (word == "normal")
        {
          priority = NORMAL;
        }
        else if (word == "high")
        {
          priority = HIGH;
        }
        else
        {
          throw std::invalid_argument("<INVALID COMMAND>");
        }

        std::string element = "";
        iss.get();
        std::getline(iss, element);

        if (element.empty())
        {
          throw std::invalid_argument("<INVALID COMMAND>");
        }

        queue.putElementToQueue(element, priority);
      }
      else if (word == "get")
      {
        std::cout << queue.getElementFromQueue() << "\n";
      }
      else if (word == "accelerate")
      {
        queue.accelerate();
      }
      else
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << "\n";
    }
  }

  return;
}
