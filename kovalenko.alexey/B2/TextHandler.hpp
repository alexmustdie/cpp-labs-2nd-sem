#ifndef TEXTHANDLER
#define TEXTHANDLER

#include <iostream>
#include <stdexcept>
#include <vector>
#include <iterator>
#include <cctype>
#include <locale>
#include "ReadState.hpp"

template<typename Iter>
class TextHandler
{
public:
  TextHandler(size_t line_width);
  ~TextHandler();
  
  void handle(Iter begin, Iter end);
  void addNewWord();
  
  bool readWord();
  bool readNumber();
  bool readSyntex();
  bool readSpace();

private:
  ReadState* state_;
  const size_t line_width_;
  std::vector<char> string_;
  std::vector<char> word_;
  Iter iter_;
  Iter end_;
};

template<typename Iter>
TextHandler<Iter>::TextHandler(size_t line_width):
  state_(new ReadState()),
  line_width_(line_width),
  string_({}),
  word_({}),
  iter_(nullptr),
  end_(nullptr)
{}

template<typename Iter>
TextHandler<Iter>::~TextHandler()
{
  delete state_;
}

template<typename Iter>
void TextHandler<Iter>::handle(Iter begin, Iter end)
{
  if (begin == end)
  {
    return;
  }

  iter_ = begin;
  end_ = end;
  
  iter_--;

  while (iter_ != end_)
  {
    iter_++;
    
    if (!(readWord() || readNumber() || readSpace() || readSyntex()))
    {
      return;
    }
  }

  addNewWord();
  
  if (!string_.empty())
  {
    std::copy(string_.begin(), string_.end() - 1, std::ostream_iterator<char>(std::cout));
    std::cout << "\n";
  }
}

template<typename Iter>
void TextHandler<Iter>::addNewWord()
{
  size_t word_size = word_.size(),
    string_size = string_.size();

  if (string_size + word_size < line_width_)
  {
    string_.insert(string_.end(), word_.begin(), word_.end());
    
    if (!string_.empty())
    {
      string_.push_back(' ');
    }
  }
  else 
  {
    if (string_size + word_size == line_width_)
    {
      std::copy(string_.begin(), string_.end(), std::ostream_iterator<char>(std::cout));
      std::copy(word_.begin(), word_.end(), std::ostream_iterator<char>(std::cout));
      std::cout << "\n";
      
      string_.clear();
    }
    else
    {
      std::copy(string_.begin(), string_.end() - 1, std::ostream_iterator<char>(std::cout));
      std::cout << "\n";
      
      string_.clear();
      std::vector<char>::iterator begin = word_.begin();
      
      string_.insert(string_.end(), begin, word_.end());
      string_.push_back(' ');
    }
  }

  word_.clear();
  state_->setWord();
}

template<typename Iter>
bool TextHandler<Iter>::readWord()
{
  std::locale cloc("C");
  
  if (std::isalpha(*iter_, cloc))
  {
    if (state_->getNewWord())
    {
      addNewWord();
    }
  }
  else
  {
    return false;
  }

  while (iter_ != end_)
  {
    if (std::isalpha(*iter_, cloc))
    {
      word_.push_back(*iter_);
    }
    else
    {
      if (*iter_ == '-')
      {
        word_.push_back(*iter_);
        break;
      }
      else
      {
        iter_--;
        break;
      }
    }

    iter_++;
  }

  if (word_.size() > 20)
  {
    throw std::invalid_argument("Too long word");
  }

  return true;
}

template<typename Iter>
bool TextHandler<Iter>::readNumber()
{
  std::locale cloc("C");
  
  if (isdigit(*iter_, cloc) || *iter_ == '+')
  {
    addNewWord();
  }
  else
  {
    if (*iter_ == '-' && isdigit(*(iter_+1), cloc))
    {
     ++iter_;
      addNewWord();
      word_.push_back('-');
    }
    else
    {
      return false;
    }
  }

  char point = std::use_facet< std::numpunct<char> >(std::cin.getloc()).decimal_point();

  while (iter_ != end_)
  {
    if (isdigit(*iter_, cloc) || *iter_ == point || *iter_ == '+')
    {
      word_.push_back(*iter_);
    }
    else
    {
      iter_--;
      break;
    }

    iter_++;
  }

  if (word_.size() > 20)
  {
    throw std::invalid_argument("Too long number");
  }

  return true;
}


template<typename Iter>
bool TextHandler<Iter>::readSyntex()
{
  if (*iter_ == '-')
  {
    state_->setDash();

    if (*(++iter_) == '-' && *(++iter_) == '-')
    {
      word_.push_back(' ');

      for (size_t i = 0; i < 3; i++)
      {
        word_.push_back('-');
      }
    }
    else
    {
      throw std::invalid_argument("Unexpected symbol");
    }
  }
  else
  {
    if (ispunct(*iter_))
    {
      if (*iter_ == ',')
      {
        state_->setComma();
      }
      else
      {
        state_->setSyntax();
      }

      word_.push_back(*iter_);
    }
    else
    {
      return false;
    }
  }

  return true;
}

template<typename Iter>
bool TextHandler<Iter>::readSpace()
{
  if (isspace(*iter_))
  {
    state_->setSpace();
    
    while (iter_ != end_)
    {
      if (!isspace(*iter_))
      {
        iter_--;
        break;
      }

      iter_++;
    }
  }
  else
  {
    return false;
  }

  return true;
}

#endif
