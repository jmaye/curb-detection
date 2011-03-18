#ifndef DEM_H
#define DEM_H

#include "PointCloud.h"
#include "Cell.h"
#include "DEMVisitor.h"

#include <iosfwd>
#include <vector>

#include <stdint.h>

class DEM {
  friend std::ostream& operator << (std::ostream& stream,
    const DEM& obj);
  friend std::istream& operator >> (std::istream& stream,
    DEM& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const DEM& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    DEM& obj);

  DEM(const DEM& other);
  DEM& operator = (const DEM& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  double mf64CellSizeX;
  double mf64CellSizeY;
  uint32_t mu32CellsNbrX;
  uint32_t mu32CellsNbrY;
  double mf64MinX;
  double mf64HeightMin;
  double mf64HeightMax;
  std::vector<Cell> mCellsVector;
  std::vector<uint32_t> mLabelsVector;

public:
  DEM(const PointCloud& pointCloud, double f64CellSizeX = 0.4,
    double f64CellSizeY = 0.4, uint32_t u32CellsNbrX = 20,
    uint32_t u32CellsNbrY = 20, double f64MinX = 1, double f64HeightMin = -10,
    double f64HeightMax = 10);
  ~DEM();

  void accept(DEMVisitor& v) const;

  const std::vector<Cell>& getCellsVector() const;
  uint32_t getCellsNbrX() const;
  uint32_t getCellsNbrY() const;
  void setLabelsVector(const std::vector<uint32_t>& labelsVector);
  const std::vector<uint32_t>& getLabelsVector() const;

protected:

};

#endif // DEM_H
