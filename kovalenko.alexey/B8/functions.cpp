#include <cmath>
#include <iterator>
#include <algorithm>
#include "functions.hpp"

void printVector(const std::vector<Shape *> &tmp)
{
  std::for_each(tmp.begin(), tmp.end(), [](const Shape *shape) { shape->draw(std::cout); });
}

void doTask2()
{
  auto shapes = createShapesVector();
  std::cout << "Original:\n";
  printVector(shapes);

  std::sort(shapes.begin(), shapes.end(), [](const Shape *shape1, const Shape *shape2) {
    return (shape1->isMoreLeft(*shape2));
  });
  std::cout << "Left-Right:\n";
  printVector(shapes);

  std::sort(shapes.begin(), shapes.end(), [](const Shape *shape1, const Shape *shape2) {
    return !(shape1->isMoreLeft(*shape2));
  });
  std::cout << "Right-Left:\n";
  printVector(shapes);

  std::sort(shapes.begin(), shapes.end(), [](const Shape *shape1, const Shape *shape2) {
    return (shape1->isUpper(*shape2));
  });
  std::cout << "Top-Bottom:\n";
  printVector(shapes);

  std::sort(shapes.begin(), shapes.end(), [](const Shape *shape1, const Shape *shape2) {
    return !(shape1->isUpper(*shape2));
  });
  std::cout << "Bottom-Top:\n";
  printVector(shapes);
  for (auto &shape : shapes) {
    delete shape;
  }
}

void removeFromString(std::string& input, const std::vector<char>& chars) {
  for(auto c: chars) {
    input.erase(std::remove(input.begin(), input.end(), c), input.end());
  }
}

std::vector<Shape *> createShapesVector()
{
  std::vector<Shape *> shapes;
  std::string fileString, name;
  char c = ' ';
  int x, y;
  while (std::getline(std::cin, fileString) && fileString != "STOP") {
    removeFromString(fileString, {'\t', ' '});
    if (fileString.empty()) {
      continue;
    }
    std::istringstream in(fileString);
    std::getline(in, name, '(');
    name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
    if (in) {
      in >> x ;
      if (!(in)) {
        throw std::invalid_argument("Format error - X");
      }
      in >> c;
      if (c != ';') {
        throw std::invalid_argument("Format error - ;");
      }
      in >> y;
      if (!in) {
        throw std::invalid_argument("Format error - Y");
        throw std::invalid_argument("Format error - Y");
      }
      in >> c;
      if (!(in && (c == ')'))) {
        throw std::invalid_argument("Format error - )");
      }
      if (name == "TRIANGLE") {
        shapes.push_back(new Triangle(x, y));
      } else if (name == "SQUARE") {
        shapes.push_back(new Square(x, y));
      } else if (name == "CIRCLE") {
        shapes.push_back(new Circle(x, y));
      } else {
        throw std::invalid_argument("Format error - Figure name or (");
      }
    }
  }
  return shapes;
}

void doTask1()
{
  std::vector<double> mainVector{std::istream_iterator<double>(std::cin), std::istream_iterator<double>()};
  if (!std::cin.eof()) {
    throw std::invalid_argument("invalid");
  }
  if (mainVector.empty()) {
    return;
  }
  std::transform(mainVector.begin(), mainVector.end(), mainVector.begin(),
                 std::bind2nd(std::multiplies<double>(), M_PI));
  std::copy(mainVector.begin(), mainVector.end(), std::ostream_iterator<double>(std::cout, "\n"));
}
