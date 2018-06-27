#include "factorialContainer.hpp"

Container::Iterator Container::begin()
{
  return Container::Iterator(1);
}

Container::Iterator Container::end()
{
  return Container::Iterator(11);
}

Container::Iterator::Iterator(size_t index) :
  value_(factorial(index)),
  index_(index)
{}

Container::Iterator& Container::Iterator::operator++()
{
  index_++;
  value_ = factorial(index_);
  return *this;
}

Container::Iterator Container::Iterator::operator++(int)
{
  Iterator old = *this;

  index_++;
  value_ *= factorial(index_);
  return *this;

  return old;
}

Container::Iterator& Container::Iterator::operator--()
{
  index_--;
  value_ = factorial(index_);
  return *this;
}

Container::Iterator Container::Iterator::operator--(int)
{
  Iterator old = *this;
  index_--;
  value_ *= factorial(index_);
  return *this;
  return old;
}

bool Container::Iterator::operator==(const Iterator &other) const
{
  return (index_ == other.index_);
}

bool Container::Iterator::operator!=(const Iterator &other) const
{
  return (index_ != other.index_);
}

size_t Container::Iterator::factorial(const size_t size)
{
  size_t multiplication = size;
  for (size_t i = 1; i < size; i++)
  {
    multiplication *= i;
  }
  return multiplication;
}

const size_t & Container::Iterator::operator*() const
{
  return value_;
}

const size_t * Container::Iterator::operator->() const
{
  return &value_;
}
