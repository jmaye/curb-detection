#ifndef EDGE_H
#define EDGE_H

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

public:
  Edge();
  Edge(const Edge& other);
  Edge& operator = (const Edge& other);
  ~Edge();

  double mf64Weight;
  uint32_t mu32Node1Idx;
  uint32_t mu32Node2Idx;

protected:

};

class EdgeCompare {
public:
  bool operator() (const Edge& lhs, const Edge& rhs) const {
    return lhs.mf64Weight < rhs.mf64Weight;
  }
};

#endif // EDGE_H
