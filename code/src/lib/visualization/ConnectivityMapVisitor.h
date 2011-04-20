#ifndef CONNECTIVITYMAPVISITOR_H
#define CONNECTIVITYMAPVISITOR_H

#include "Visitor.h"

#include <GL/gl.h>

#include <iosfwd>

class ConnectivityMap;

class ConnectivityMapVisitor : public Visitor {
  friend std::ostream& operator << (std::ostream& stream,
    const ConnectivityMapVisitor& obj);
  friend std::istream& operator >> (std::istream& stream,
    ConnectivityMapVisitor& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const ConnectivityMapVisitor& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    ConnectivityMapVisitor& obj);

  ConnectivityMapVisitor(const ConnectivityMapVisitor& other);
  ConnectivityMapVisitor& operator = (const ConnectivityMapVisitor& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  ConnectivityMapVisitor();
  ~ConnectivityMapVisitor();

  void visit(const ConnectivityMap* connectivityMap);

protected:

};

#endif // CONNECTIVITYMAPVISITOR_H
