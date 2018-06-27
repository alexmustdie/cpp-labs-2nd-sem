#include "part.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <numeric>
#include <vector>
#include <string>
#include <locale>

struct Point
{
  int x, y;
};

using Shape = std::vector< Point >;

class Line : public std::string
{
  friend std::istream& operator>>(std::istream &in, Line &line)
  {
    while(std::getline(in, line))
    {
      if(line.empty())
      {
        continue;
      }
      if(std::find_if(line.begin(), line.end(), 
        [](char c) {return !std::isspace(c, std::locale()); }) != line.end())
      {
        break;
      }
    }
    return in;
  }
};

Shape getShapeFromLine(const Line &line)
{
  std::stringstream stream(line);

  int n;
  stream >> n;

  Shape shape;

  for(int i = 0; i < n; i++)
  {
    Point point;
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '(');
    stream >> point.x;
    
    stream.ignore(std::numeric_limits<std::streamsize>::max(), ';');
    stream >> point.y;

    stream.ignore(std::numeric_limits<std::streamsize>::max(), ')');
    shape.push_back(point);
  }

  if(stream.fail())
  {
    throw std::invalid_argument("invalid values");
  }

  std::string remLine;
  std::getline(stream, remLine);
  if(std::find_if(remLine.begin(), remLine.end(), 
    [](char c) {return !std::isspace(c, std::locale()); }) != remLine.end())
  {
    throw std::invalid_argument("invalid input");
  }
  return shape;
}

int sqDistance(const Point &a, const Point &b)
{
  return ((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}
bool distancesMakeRightTriangle(const Shape& shape, size_t fromPoint)
{
  int distSum = 0;
  int hyp = 0;
  for(size_t i = 0; i < shape.size(); i++)
  {
    if(i == fromPoint)
    {
      continue;
    }
    int sqDist = sqDistance(shape[fromPoint], shape[i]);
    distSum += sqDist;
    hyp = std::max(hyp, sqDist);
  }
  if(distSum - hyp == hyp)
  {
    return true;
  }
  return false;
}
bool isTriangle(const Shape& shape)
{
  return (shape.size() == 3);
}
bool isRectangle(const Shape& shape)
{
  if(shape.size() != 4)
  {
    return false;
  }

  for(size_t i = 0; i < shape.size(); i++)
  {
    if(!distancesMakeRightTriangle(shape, i))
    {
      return false;
    }
  }
  return true;
}
bool isSquare(const Shape& shape)
{
  if(!isRectangle(shape))
  {
    return false;
  }

  std::vector<int> distances;
  int hyp = 0;
  for(size_t i = 1; i < shape.size(); i++)
  {
    int sqDist = sqDistance(shape[0], shape[i]);
    hyp = std::max(hyp, sqDist);
    distances.push_back(sqDist);
  }

  if(std::any_of(distances.begin(), distances.end(), [hyp](int d) { return (2 * d == hyp); }))
  {
    return true;
  }
  return false;
}
bool correctShapeOrder(const Shape &a, const Shape &b)
{
  if(isRectangle(a) && isRectangle(b))
  {
    return isSquare(a);
  }
  return isTriangle(a);
}
void printPoint(const Point &p, std::ostream &out)
{
  out << " (" << p.x << ";" << p.y << ")";
}
void printShape(const Shape &shape, std::ostream &out)
{
  out << shape.size();
  std::for_each(shape.begin(), shape.end(), [&out](const Point &p) {printPoint(p, out); });
  out << "\n";
}
void optionTwo(std::istream &in, std::ostream &out)
{
  std::vector<Shape> shapes;

  std::transform(std::istream_iterator<Line>(in), std::istream_iterator<Line>(), 
    std::back_inserter(shapes), getShapeFromLine);
  
  int totalVertices = std::accumulate(shapes.begin(), shapes.end(), 0, 
    [](int sum, const Shape &sh) {return sum + sh.size(); });
  out << "Vertices: " << totalVertices << std::endl;

  int triangles = std::count_if(shapes.begin(), shapes.end(), isTriangle);
  out << "Triangles: " << triangles << std::endl;

  int squares = std::count_if(shapes.begin(), shapes.end(), isSquare);
  out << "Squares: " << squares << std::endl;

  int rectangles = std::count_if(shapes.begin(), shapes.end(), isRectangle);
  out << "Rectangles: " << rectangles << std::endl;

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), 
    [](const Shape &sh) {return sh.size() == 5; }), shapes.end());

  std::vector<Point> points;
  std::transform(shapes.begin(), shapes.end(), 
    std::back_inserter(points), [](const Shape &sh) {return sh.front(); });
  
  out << "Points:";
  std::for_each(points.begin(), points.end(), [&out](const Point &p) {printPoint(p, out); });
  out << std::endl;

  auto triangleEnd = std::partition(shapes.begin(), shapes.end(), isTriangle);
  auto squareEnd = std::partition(triangleEnd, shapes.end(), isSquare);
  std::partition(squareEnd, shapes.end(), isRectangle);

  out << "Shapes:" << std::endl;
  std::for_each(shapes.begin(), shapes.end(), [&out](const Shape &sh) {printShape(sh, out); });

}

