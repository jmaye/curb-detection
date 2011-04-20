#ifndef CURBMAPVISITOR_H
#define CURBMAPVISITOR_H

#include "Visitor.h"

#include <GL/gl.h>

#include <iosfwd>

class CurbMap;

class CurbMapVisitor : public Visitor {
  friend std::ostream& operator << (std::ostream& stream,
    const CurbMapVisitor& obj);
  friend std::istream& operator >> (std::istream& stream,
    CurbMapVisitor& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const CurbMapVisitor& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    CurbMapVisitor& obj);

  CurbMapVisitor(const CurbMapVisitor& other);
  CurbMapVisitor& operator = (const CurbMapVisitor& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  CurbMapVisitor();
  ~CurbMapVisitor();

  void visit(const CurbMap* curbMap);

protected:

};

#endif // CURBMAPVISITOR_H
