#ifndef COMPONENT_H
#define COMPONENT_H

#include "InvalidOperationException.h"
#include "OutOfBoundException.h"

#include <iosfwd>
#include <list>

#include <stdint.h>

class Component {
  friend std::ostream& operator << (std::ostream& stream,
    const Component& obj);
  friend std::istream& operator >> (std::istream& stream,
    Component& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const Component& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    Component& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  double mf64Int;

public:
  Component();
  Component(uint32_t u32Idx);
  ~Component();
  Component(const Component& other);
  Component& operator = (const Component& other);

  std::list<uint32_t> mNodesIndexList;

  double compare(const Component& other, uint32_t u32K) const
    throw (InvalidOperationException);

  double getInt() const;
  const std::list<uint32_t>& getNodesIndexList() const;
  void setInt(double f64Int) throw (OutOfBoundException);
  void setNodesIndexList(const std::list<uint32_t>& nodesIndexList);

protected:

};

#endif // COMPONENT_H
