#ifndef UNIGAMMA_H
#define UNIGAMMA_H

#include "UniDistribution.h"
#include "OutOfBoundException.h"

#include <iosfwd>

class UniGamma : public UniDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const UniGamma& obj);
  friend std::istream& operator >> (std::istream& stream,
    UniGamma& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const UniGamma& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    UniGamma& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  double mf64Alpha;
  double mf64Beta;

public:
  UniGamma(double f64Alpha, double f64Beta) throw (OutOfBoundException);
  UniGamma(const UniGamma& other);
  UniGamma& operator = (const UniGamma& other);
  ~UniGamma();

  double pdf(double f64X) const throw (OutOfBoundException);
  double logpdf(double f64X) const throw (OutOfBoundException);
  double getAlpha() const;
  double getBeta() const;
  void setAlpha(double f64Alpha) throw (OutOfBoundException);
  void setBeta(double f64Beta) throw (OutOfBoundException);

protected:

};

#endif // UNIGAMMA_H
