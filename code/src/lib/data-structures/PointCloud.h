#ifndef POINTCLOUDETH_H
#define POINTCLOUDETH_H

#include "Point3D.h"
#include "PointCloudVisitor.h"
#include "OutOfBoundException.h"
#include "IOException.h"

#include <iosfwd>
#include <vector>

#include <stdint.h>

class PointCloudETH {
  friend std::ostream& operator << (std::ostream& stream,
    const PointCloudETH& obj);
  friend std::istream& operator >> (std::istream& stream, PointCloudETH& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const PointCloudETH& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, PointCloudETH& obj);

  PointCloudETH(const PointCloudETH& other);
  PointCloudETH& operator = (const PointCloudETH& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream) throw (IOException);
  virtual void write(std::ofstream& stream) const;

  std::vector<Point3D> mPointsVector;

public:
  PointCloudETH();
  ~PointCloudETH();

  const Point3D& operator [] (uint32_t u32Idx) const
    throw (OutOfBoundException);
  void accept(PointCloudVisitor& v) const;
  uint32_t getSize() const;

protected:

};

#endif // POINTCLOUDETH_H
