#ifndef CURBMAP_H
#define CURBMAP_H

#include "Point3D.h"
#include "CurbMapVisitor.h"

#include <iosfwd>
#include <vector>

class CurbMap {
  friend std::ostream& operator << (std::ostream& stream,
    const CurbMap& obj);
  friend std::istream& operator >> (std::istream& stream,
    CurbMap& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const CurbMap& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    CurbMap& obj);

  CurbMap(const CurbMap& other);
  CurbMap& operator = (const CurbMap& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  std::vector<Point3D> mCurbPointsVector;

public:
  CurbMap();
  ~CurbMap();

  void insert(Point3D curbPoint);

  void accept(CurbMapVisitor& v) const;

  const std::vector<Point3D>& getCurbPointsVector() const;

protected:

};

#endif // CURBMAP_H
