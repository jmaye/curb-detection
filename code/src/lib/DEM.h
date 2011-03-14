#ifndef DEM_H
#define DEM_H

#include <iosfwd>

class DEM {
  friend std::ostream& operator << (std::ostream& stream,
    const DEM& obj);
  friend std::istream& operator >> (std::istream& stream,
    DEM& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const DEM& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    DEM& obj);

  DEM(const DEM& other);
  DEM& operator = (const DEM& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  DEM();
  ~DEM();

protected:

};

#endif // DEM_H
