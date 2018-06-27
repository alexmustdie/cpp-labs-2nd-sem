#ifndef FACTORIAL
#define FACTORIAL

#include <iterator>

class Container
{
public:
  class Iterator;
  Container() = default;
  Iterator begin();
  Iterator end();
};

class Container::Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
{
public:
  Iterator(size_t index);
  Iterator& operator++();
  Iterator operator++(int);
  Iterator& operator--();
  Iterator operator--(int);
  const size_t & operator *() const;
  const size_t * operator ->() const;
  bool operator ==(const Iterator &other) const;
  bool operator !=(const Iterator &other) const;

private:
  size_t value_;
  size_t index_;
  size_t factorial(size_t);
};


#endif
