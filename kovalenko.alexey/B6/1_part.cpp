#include "part.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <list>
#include <map>

bool isPrintedAndSet(const std::string &word, std::map<std::string, bool> &isPrinted)
{
  auto it = isPrinted.find(word);
  if(it->second == false)
  {
    it->second = true;
    return true;
  }
  else
  {
    return false;
  }
}
void optionOne(std::istream &in, std::ostream &out)
{
  std::list<std::string> words;
  std::copy(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>(), std::back_inserter(words));

  std::map<std::string, bool> isPrinted;
  std::transform(words.begin(), words.end(), std::inserter(isPrinted, isPrinted.begin()),
    [](const std::string &word) {return std::pair<std::string, bool>(word, false); });

  std::copy_if(words.begin(), words.end(), std::ostream_iterator<std::string>(out, "\n"),
    [&](const std::string &word) {return isPrintedAndSet(word, isPrinted); });
}

