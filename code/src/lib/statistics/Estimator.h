#ifndef ESTIMATOR_H
#define ESTIMATOR_H

#include <iosfwd>

class Estimator {
  friend std::ostream& operator << (std::ostream& stream,
    const Estimator& obj);
  friend std::istream& operator >> (std::istream& stream,
    Estimator& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const Estimator& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    Estimator& obj);

  Estimator(const Estimator& other);
  Estimator& operator = (const Estimator& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  Estimator();
  ~Estimator();

protected:

};

#endif // ESTIMATOR_H
