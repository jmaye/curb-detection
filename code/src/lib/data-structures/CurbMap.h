#ifndef CURBMAP_H
#define CURBMAP_H

#include "DEM.h"

#include <iosfwd>

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

//  double mf64CellSizeX;
//  double mf64CellSizeY;
//  uint32_t mu32CellsNbrX;
//  uint32_t mu32CellsNbrY;
//  double mf64XOffset;
//  double mf64YOffset;

public:
  CurbMap(const DEM& dem);
  ~CurbMap();

protected:

};

#endif // CURBMAP_H
