#ifndef COMPONENT_H
#define COMPONENT_H

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

public:
  Component();
  ~Component();
  Component(const Component& other);
  Component& operator = (const Component& other);

  double mf64Int;
  std::list<uint32_t> mNodesIndexList;

protected:

};

#endif // COMPONENT_H
