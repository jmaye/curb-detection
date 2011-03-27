#ifndef EDGE_H
#define EDGE_H

#include "OutOfBoundException.h"

#include <iosfwd>

#include <stdint.h>

class Edge {
  friend std::ostream& operator << (std::ostream& stream,
    const Edge& obj);
  friend std::istream& operator >> (std::istream& stream,
    Edge& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const Edge& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    Edge& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  double mf64Weight;
  uint32_t mu32Node1Idx;
  uint32_t mu32Node2Idx;

public:
  Edge(double f64Weight, uint32_t u32Node1Idx, uint32_t u32Node2Idx)
    throw (OutOfBoundException);
  Edge(const Edge& other);
  Edge& operator = (const Edge& other);
  ~Edge();

  double getWeight() const;
  uint32_t getNode1Idx() const;
  uint32_t getNode2Idx() const;
  void setWeight(double f64Weight) throw (OutOfBoundException);
  void setNode1Idx(uint32_t u32Node1Idx);
  void setNode2Idx(uint32_t u32Node2Idx);

protected:

};

class EdgeCompare {
public:
  bool operator() (const Edge& lhs, const Edge& rhs) const {
    return lhs.getWeight() < rhs.getWeight();
  }
};

#endif // EDGE_H
