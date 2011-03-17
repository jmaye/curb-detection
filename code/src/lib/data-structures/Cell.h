#ifndef CELL_H
#define CELL_H

#include "DEMVisitor.h"
#include "UniGaussian.h"
#include "MLEstimator.h"
#include "Point2D.h"

#include <iosfwd>
#include <vector>

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
  MLEstimator mEstimator;
  Point2D mCellCenter;
  Point2D mCellSize;

public:
  std::vector<double> mLabelVector;

public:
  Cell(const UniGaussian& heightDist, const MLEstimator& estimator,
    const Point2D& cellCenter, const Point2D& cellSize);
  ~Cell();
  Cell(const Cell& other);
  Cell& operator = (const Cell& other);

  void accept(const DEMVisitor& v) const;
  void addPoint(double f64Height);
  double compare(const Cell& other) const;

  const UniGaussian& getHeightDist() const;
  void setHeightDist(const UniGaussian& heightDist);
  const MLEstimator& getEstimator() const;
  void setEstimator(const MLEstimator& estimator);
  const Point2D& getCellCenter() const;
  void setCellCenter(const Point2D& cellCenter);
  const Point2D& getCellSize() const;
  void setCellSize(const Point2D& cellSize);

protected:

};

#endif // CELL_H
