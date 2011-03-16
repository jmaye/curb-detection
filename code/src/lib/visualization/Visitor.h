#ifndef VISITOR_H
#define VISITOR_H

#include <GL/gl.h>

#include <iosfwd>
#include <vector>

class Visitor {
  friend std::ostream& operator << (std::ostream& stream,
    const Visitor& obj);
  friend std::istream& operator >> (std::istream& stream,
    Visitor& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const Visitor& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    Visitor& obj);

  Visitor(const Visitor& other);
  Visitor& operator = (const Visitor& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  Visitor();
  ~Visitor();

  virtual void draw() const;

protected:
  std::vector<GLuint> mGLListVector;
};

#endif // VISITOR_H
