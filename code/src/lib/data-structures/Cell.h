#ifndef CELL_H
#define CELL_H

#include "DEMVisitor.h"

#include <iosfwd>
#include <vector>

#include <stdint.h>

class Cell {
  friend std::ostream& operator << (std::ostream& stream,
    const Cell& obj);
  friend std::istream& operator >> (std::istream& stream,
    Cell& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const Cell& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    Cell& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  double mf64HeightMean;
  double mf64HeightVariance;
  std::vector<double> mLabelVector;
  double mf64CenterX;
  double mf64CenterY;
  double mf64CellSizeX;
  double mf64CellSizeY;
  uint32_t mu32PointsNbr;

public:
  Cell();
  ~Cell();
  Cell(const Cell& other);
  Cell& operator = (const Cell& other);

  void accept(const DEMVisitor& v) const;
  void addPoint(double f64Height);

protected:

};

#endif // CELL_H
