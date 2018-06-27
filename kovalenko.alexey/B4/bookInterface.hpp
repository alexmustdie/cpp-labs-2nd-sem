#ifndef MISSIONNOTEBOOK
#define MISSIONNOTEBOOK

#include <iostream>
#include <sstream>
#include <string>
#include "notebook.hpp"

std::string editName(const std::string &name)
{
  if (name.empty())
  {
    return name;
  }
  if ((name.front() != '\"') || (name.back() != '\"'))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string formatted;
  for (size_t i = 1; i < name.size() - 1; i++)
  {
    if (name[i] != '\\')
    {
      formatted.push_back(name[i]);
    }
  }
  return formatted;
}

std::string readNumber(std::stringstream &in)
{
  std::string number;
  in >> number;

  for (auto i = number.begin(); i != number.end(); i++)
  {
    if (!isdigit(*i))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  return number;
}

std::string readName(std::stringstream &in)
{
  in.ignore();
  std::string name;
  std::getline(in, name);
  return editName(name);
}

std::string readMarkName(std::stringstream &in)
{
  std::string markName;
  in >> markName;
  for (auto it = markName.begin(); it != markName.end(); it++)
  {
    if ((!isalnum(*it)) && (*it != '-'))
    {
      throw std::invalid_argument("<INVALID BOOKMARK>");
    }
  }
  return markName;
}

void bookInterface()
{
  Notebook phonebook;
  std::string string;
  while (std::getline(std::cin, string))
  {
    try
    {
      std::stringstream stream(string);

      std::string command;
      stream >> command;

      if (command == "add")
      {
        std::string number = readNumber(stream);
        std::string name = readName(stream);
        phonebook.addNewRecord(Notebook::PhonebookEntry{ number, name });
      }
      else if (command == "store")
      {
        std::string oldMarkName = readMarkName(stream);
        std::string newMarkName = readMarkName(stream);
        phonebook.addMarkName(oldMarkName, newMarkName);
      }
      else if (command == "insert")
      {
        std::string place;
        stream >> place;

        if ((place != "before") && (place != "after"))
        {
          throw std::invalid_argument("<INVALID COMMAND>");
        }
        std::string markName = readMarkName(stream);
        std::string number = readNumber(stream);
        std::string name = readName(stream);

        if (place == "after")
        {
          phonebook.insertAfter(markName, Notebook::PhonebookEntry{ number,name });
        }
        else
        {
          phonebook.insertBefore(markName, Notebook::PhonebookEntry{ number,name });
        }
      }
      else if (command == "delete")
      {
        std::string markName = readMarkName(stream);
        phonebook.deleteRecord(markName);
      }
      else if (command == "show")
      {
        std::string markName = readMarkName(stream);
        phonebook.showName(markName);
      }
      else if (command == "move")
      {
        std::string markName = readMarkName(stream);
        std::string steps;
        stream >> steps;
        try
        {
          int stepsInt = std::stoi(steps);
          phonebook.moveMark(markName, stepsInt);
        }
        catch (const std::invalid_argument&)
        {
          phonebook.moveMark(markName, steps);
        }
      }
      else
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }

    }
    catch (const std::invalid_argument &e)
    {
      std::cout << e.what() << std::endl;
    }
  }
}

#endif
