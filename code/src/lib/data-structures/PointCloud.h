#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "data-structures/Point3D.h"
#include "exceptions/OutOfBoundException.h"
#include "exceptions/IOException.h"

#include <iosfwd>
#include <vector>

#include <stdint.h>

class PointCloud {
  friend std::ostream& operator << (std::ostream& stream,
    const PointCloud& obj);
  friend std::istream& operator >> (std::istream& stream, PointCloud& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const PointCloud& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, PointCloud& obj);

  PointCloud(const PointCloud& other);
  PointCloud& operator = (const PointCloud& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream) throw (IOException);
  virtual void write(std::ofstream& stream) const;

  std::vector<Point3D> mPointsVector;

public:
  PointCloud();
  ~PointCloud();

  const Point3D& operator [] (uint32_t u32Idx) const
    throw (OutOfBoundException);
  uint32_t getSize() const;
  void clear();

protected:

};

#endif // POINTCLOUD_H
