#include <iostream>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <string>
#include <ctype.h>
#include <vector>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

int getKey(std::string &line)
{
  std::string key_str = line.substr(0, line.find(","));
  line.erase(0, key_str.size() + 1);

  if (line.empty())
  {
    throw std::invalid_argument("String is empty");
  }

  if (key_str[0] == ' ')
  {
    key_str.erase(0, 1);
  }

  if (std::isdigit(key_str[0])
    || (key_str[0] == '-' && std::isdigit(key_str[1])))
  {
    int key = stoi(key_str);

    if (key < -5 || key > 5)
    {
      throw std::invalid_argument("Key must be from -5 to 5");
    }

    return key;
  }
  else
  {
    throw std::invalid_argument("Key is not number");
  }
}

bool compare(const DataStruct& struct_1, const DataStruct& struct_2)
{
  if (struct_1.key1 != struct_2.key1)
  {
    return struct_1.key1 < struct_2.key1;
  }
  else if (struct_1.key2 != struct_2.key2)
  {
    return struct_1.key2 < struct_2.key2;
  }
  else
  {
    return struct_1.str.size() < struct_2.str.size();
  }
}

int main()
{
  try
  {
    std::vector<DataStruct> vector;
    std::string line = "";
    
    while (std::getline(std::cin, line))
    {
      std::istringstream iss(line);

      int key1 = getKey(line);
      int key2 = getKey(line);

      if (line[0] == ' ')
      {
        line.erase(0, 1);
      }

      vector.push_back({key1, key2, line});
    }

    std::sort(vector.begin(), vector.end(), compare);

    for (DataStruct it: vector)
    {
      std::cout << it.key1 << "," << it.key2 << "," << it.str << "\n";
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
