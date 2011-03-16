#ifndef UNIGAUSSIAN_H
#define UNIGAUSSIAN_H

#include <iosfwd>

class UniGaussian {
  friend std::ostream& operator << (std::ostream& stream,
    const UniGaussian& obj);
  friend std::istream& operator >> (std::istream& stream,
    UniGaussian& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const UniGaussian& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    UniGaussian& obj);

  UniGaussian(const UniGaussian& other);
  UniGaussian& operator = (const UniGaussian& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  double mf64Mean;
  double mf64Variance;

public:
  UniGaussian(double f64Mean, double f64Variance);
  ~UniGaussian();

  double pdf(double f64X) const;
  void addDataPoint(double f64Z);
  double getMean() const;
  double getVariance() const;
  void setMean(double f64Mean);
  void setVariance(double f64Variance);

protected:

};

#endif // UNIGAUSSIAN_H
