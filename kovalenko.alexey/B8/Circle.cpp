#include "Circle.hpp"

void Circle::draw(std::ostream &stream) const
{
  stream << "CIRCLE " << '(' << x_ << "; " << y_ << ")\n";
}

Circle::Circle(const int setX, const int setY) : Shape(setX, setY)
{
}
