#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape {
public:
  Triangle(int x, int y);

  void draw(std::ostream &stream) const override;
};

#endif
