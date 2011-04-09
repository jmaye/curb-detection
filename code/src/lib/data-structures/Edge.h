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
  std::pair<uint32_t, uint32_t> mNode1;
  std::pair<uint32_t, uint32_t> mNode2;

public:
  Edge(double f64Weight, const std::pair<uint32_t, uint32_t>& mNode1,
    const std::pair<uint32_t, uint32_t>& mNode2) throw (OutOfBoundException);
  Edge(const Edge& other);
  Edge& operator = (const Edge& other);
  ~Edge();

  double getWeight() const;
  const std::pair<uint32_t, uint32_t>& getNode1() const;
  const std::pair<uint32_t, uint32_t>& getNode2() const;

  void setWeight(double f64Weight) throw (OutOfBoundException);
  void setNode1(const std::pair<uint32_t, uint32_t>& node1);
  void setNode2(const std::pair<uint32_t, uint32_t>& node2);

protected:

};

class EdgeCompare {
public:
  bool operator() (const Edge& lhs, const Edge& rhs) const {
    return lhs.getWeight() < rhs.getWeight();
  }
};

#endif // EDGE_H
