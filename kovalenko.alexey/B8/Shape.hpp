#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

class Shape {
public:
  Shape(int x, int y);

  virtual ~Shape() = default;

  bool isMoreLeft(const Shape &tmp) const;

  bool isUpper(const Shape &tmp) const;

  virtual void draw(std::ostream &stream) const = 0;

protected:
  int x_, y_;
};

#endif

