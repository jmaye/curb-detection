#ifndef POINT3D_H
#define POINT3D_H

#include "PointCloudVisitor.h"

#include <iosfwd>

class Point3D {
  friend std::ostream& operator << (std::ostream& stream, const Point3D& obj);
  friend std::istream& operator >> (std::istream& stream, Point3D& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const Point3D& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Point3D& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  Point3D();
  Point3D(double f64X, double f64Y, double f64Z);
  ~Point3D();
  Point3D(const Point3D& other);
  Point3D& operator = (const Point3D& other);

  void accept(const PointCloudVisitor& v) const;

  double mf64X;
  double mf64Y;
  double mf64Z;

protected:

};

#endif // POINT3D_H
