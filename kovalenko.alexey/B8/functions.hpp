#ifndef FUNTIONS_HPP
#define FUNTIONS_HPP

#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include "circle.hpp"
#include "triangle.hpp"
#include "Square.hpp"

void printShape(const std::vector<Shape *> &tmp);

void doTask1();

void doTask2();

std::vector<Shape *> createShapesVector();

#endif
