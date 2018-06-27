#include "Square.hpp"

void Square::draw(std::ostream &stream) const
{
  stream << "SQUARE " << '(' << x_ << "; " << y_ << ")\n";
}

Square::Square(const int x, const int y) :
  Shape(x, y)
{
}
