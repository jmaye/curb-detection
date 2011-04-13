#ifndef DEM_H
#define DEM_H

#include "PointCloud.h"
#include "Cell.h"
#include "DEMVisitor.h"
#include "OutOfBoundException.h"
#include "InvalidOperationException.h"

#include <iosfwd>
#include <vector>
#include <map>

#include <stdint.h>

class DEMCRF;

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

  Cell& getCell(uint32_t u32Row, uint32_t u32Column)
    throw (OutOfBoundException);
  Cell& operator () (uint32_t u32Row, uint32_t u32Column)
    throw (OutOfBoundException);

  double mf64CellSizeX;
  double mf64CellSizeY;
  uint32_t mu32CellsNbrX;
  uint32_t mu32CellsNbrY;
  double mf64XOffset;
  double mf64YOffset;
  double mf64HeightMin;
  double mf64HeightMax;
  std::vector<std::vector<Cell> > mCellsMatrix;
  uint32_t mu32ValidCellsNbr;
  uint32_t mu32LabelsNbr;
  uint32_t mu32MinPointsPerPlane;

public:
  DEM(const PointCloud& pointCloud, double f64CellSizeX = 0.4,
    double f64CellSizeY = 0.4, uint32_t u32CellsNbrX = 20,
    uint32_t u32CellsNbrY = 20, double f64XOffset = 1, double f64YOffset = 0,
    double f64HeightMin = -10, double f64HeightMax = 10,
    uint32_t u32MinPointsPerPlane = 3) throw (OutOfBoundException);
  ~DEM();

  void accept(DEMVisitor& v) const;

  uint32_t getCellsNbrX() const;
  uint32_t getCellsNbrY() const;
  uint32_t getValidCellsNbr() const;
  uint32_t getLabelsNbr() const;
  const Cell& operator () (uint32_t u32Row, uint32_t u32Column) const
    throw (OutOfBoundException);
  uint32_t getMinPointsPerPlane() const;

  void setInitialLabels(const std::map<std::pair<uint32_t, uint32_t>, uint32_t>&
    labelsMap, const std::map<uint32_t, uint32_t>& supportsMap)
    throw (InvalidOperationException);
  void setValidCellsNbr(uint32_t u32ValidCellsNbr);
  void setLabelsNbr(uint32_t u32LabelsNbr);
  void setLabelsDist(const DEMCRF& crf) throw (OutOfBoundException);
  void setMinPointsPerPlane(uint32_t u32MinPointsPerPlane)
    throw (OutOfBoundException);

protected:

};

#endif // DEM_H
