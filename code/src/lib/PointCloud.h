#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include <iosfwd>

#include <vector>

class PointCloud {
public:
  class Point3D {
  public:
    double mf64X;
    double mf64Y;
    double mf64Z;
    double mf64Timestamp;
  };

private:
  friend std::ostream& operator << (std::ostream& stream,
    const PointCloud& obj);
  friend std::istream& operator >> (std::istream& stream,
    PointCloud& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const PointCloud& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    PointCloud& obj);

  PointCloud(const PointCloud& other);
  PointCloud& operator = (const PointCloud& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  std::vector<Point3D> mPointVector;

public:
  PointCloud();
  ~PointCloud();

  const std::vector<Point3D>& getPointVector() const;

protected:

};

#endif // POINTCLOUD_H
