#ifndef CELL_H
#define CELL_H

#include "DEMVisitor.h"
#include "UniGaussian.h"
#include "MLEstimator.h"
#include "Point2D.h"
#include "InvalidOperationException.h"
#include "OutOfBoundException.h"

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

  UniGaussian mHeightDist;
  MLEstimator mMLEstimator;
  Point2D mCellCenter;
  Point2D mCellSize;
  bool mbInvalidFlag;
  std::vector<double> mLabelsDistVector;

public:
  Cell(const UniGaussian& heightDist, const MLEstimator& estimator,
    const Point2D& cellCenter, const Point2D& cellSize)
    throw (OutOfBoundException);
  ~Cell();
  Cell(const Cell& other);
  Cell& operator = (const Cell& other);

  void accept(const DEMVisitor& v) const;
  void addPoint(double f64Height);
  double compare(const Cell& other) const;

  const UniGaussian& getHeightDist() const;
  const MLEstimator& getMLEstimator() const;
  const Point2D& getCellCenter() const;
  const Point2D& getCellSize() const;
  const std::vector<double>& getLabelsDistVector() const;
  uint32_t getMAPLabelsDist() const throw (InvalidOperationException);
  bool getInvalidFlag() const;

  void setHeightDist(const UniGaussian& heightDist);
  void setMLEstimator(const MLEstimator& estimator);
  void setCellCenter(const Point2D& cellCenter);
  void setCellSize(const Point2D& cellSize) throw (OutOfBoundException);
  void setLabelsDistVector(const std::vector<double>& labelsDistVector)
    throw (OutOfBoundException);
  void setInvalidFlag(bool bInvalidFlag);

protected:

};

#endif // CELL_H
