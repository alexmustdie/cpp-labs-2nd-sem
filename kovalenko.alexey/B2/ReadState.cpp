#include <stdexcept>
#include "ReadState.hpp"

ReadState::ReadState():
  word_(false),
  syntax_(false),
  space_(true),
  comma_(false)
{};

void ReadState::setWord()
{
  word_ = true;
  syntax_ = false;
  space_ = false;
  comma_ = false;
}

void ReadState::setSyntax()
{
  if (!word_)
  {
    throw std::invalid_argument("Unexpected syntax");
  }

  if (syntax_)
  {
    throw std::invalid_argument("Syntax befor syntax");
  }

  word_ = false;
  syntax_ = true;
  space_ = true;
}

void ReadState::setComma()
{
  setSyntax();
  comma_ = true;
}

void ReadState::setDash()
{
  if (!(comma_ || word_))
  {
    throw std::invalid_argument("Unexpected syntax");
  }

  word_ = false;
  syntax_ = true;
  space_ = true;
  comma_ = false;
}

void ReadState::setSpace()
{
  space_ = true;
}

bool ReadState::getSpace() const
{
  return space_;
}

bool ReadState::getNewWord() const
{
  return (syntax_ || space_ || !word_);
}
