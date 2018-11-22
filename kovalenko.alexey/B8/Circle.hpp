#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"
#include <iostream>

class Circle : public Shape {
public:
  Circle(const int setX, const int setY);

  virtual void draw(std::ostream &stream) const;
};

#endif
