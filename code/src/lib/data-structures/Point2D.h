#ifndef POINT2D_H
#define POINT2D_H

#include <iosfwd>

class Point2D {
  friend std::ostream& operator << (std::ostream& stream,
    const Point2D& obj);
  friend std::istream& operator >> (std::istream& stream,
    Point2D& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const Point2D& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    Point2D& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  Point2D();
  Point2D(double f64X, double f64Y);
  ~Point2D();
  Point2D(const Point2D& other);
  Point2D& operator = (const Point2D& other);

  double mf64X;
  double mf64Y;

protected:

};

#endif // Point2D_H
