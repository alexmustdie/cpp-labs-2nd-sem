#ifndef SQUARE_H
#define SQUARE_H

#include "shape.hpp"

class Square : public Shape {
public:
  Square(int x, int y);

  void draw(std::ostream &stream) const override;
};

#endif 
