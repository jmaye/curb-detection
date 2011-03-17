#ifndef UNIDISTRIBUTION_H
#define UNIDISTRIBUTION_H

#include <iosfwd>

class UniDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const UniDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    UniDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const UniDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    UniDistribution& obj);

  UniDistribution(const UniDistribution& other);
  UniDistribution& operator = (const UniDistribution& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  UniDistribution();
  ~UniDistribution();

  virtual double pdf(double f64X) const = 0;
  virtual double logpdf(double f64X) const = 0;

protected:

};

#endif // UNIDISTRIBUTION_H
