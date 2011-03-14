#ifndef DEM_H
#define DEM_H

#include "PointCloud.h"

#include <iosfwd>
#include <vector>

#include <stdint.h>
#include <math.h>

class DEM {
  class Cell {
  public:
    double mf64HeightMean;
    double mf64HeightVariance;
    std::vector<double> mLabelVector;
    double mf64CenterX;
    double mf64CenterY;
    uint32_t mu32PointsNbr;
    void addPoint(double f64Height) {
      mu32PointsNbr++;
      mf64HeightMean += 1.0 / (double)mu32PointsNbr *
        (f64Height  - mf64HeightMean);
      mf64HeightVariance += 1.0 / (double)mu32PointsNbr *
        (pow(f64Height  - mf64HeightMean, 2)- mf64HeightVariance);
    }
  };

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
  double mf64HeightMax;
  double mf64HeightMin;
  std::vector<Cell> cellVector;

public:
  DEM(const PointCloud& pointCloud, double f64CellSizeX, double f64CellSizeY,
    uint32_t u32CellsNbrX, uint32_t u32CellsNbrY, double f64MinX,
    double f64HeightMax, double f64HeightMin);
  ~DEM();

protected:

};

#endif // DEM_H
