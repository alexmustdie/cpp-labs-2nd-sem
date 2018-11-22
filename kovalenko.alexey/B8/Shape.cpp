#include "Shape.hpp"

Shape::Shape(int x, int y) : x_(x), y_(y)
{
}

bool Shape::isMoreLeft(const Shape &tmp) const
{
  return (x_ < tmp.x_);
}

bool Shape::isUpper(const Shape &tmp) const
{
  return (y_ > tmp.y_);
}

