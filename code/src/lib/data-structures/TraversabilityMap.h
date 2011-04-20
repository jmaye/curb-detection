#ifndef TRAVERSABILITYMAP_H
#define TRAVERSABILITYMAP_H

#include <iosfwd>

class TraversabilityMap {
  friend std::ostream& operator << (std::ostream& stream,
    const TraversabilityMap& obj);
  friend std::istream& operator >> (std::istream& stream,
    TraversabilityMap& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const TraversabilityMap& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    TraversabilityMap& obj);

  TraversabilityMap(const TraversabilityMap& other);
  TraversabilityMap& operator = (const TraversabilityMap& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  TraversabilityMap();
  ~TraversabilityMap();

protected:

};

#endif // TRAVERSABILITYMAP_H
