/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#ifndef UNIGAUSSIAN_H
#define UNIGAUSSIAN_H

#include "statistics/UniDistribution.h"
#include "exceptions/OutOfBoundException.h"

#include <iosfwd>
#include <stdint.h>

class UniGaussian : public UniDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const UniGaussian& obj);
  friend std::istream& operator >> (std::istream& stream, UniGaussian& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const UniGaussian& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, UniGaussian& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  double mf64Mean;
  double mf64Variance;

public:
  UniGaussian(double f64Mean, double f64Variance) throw (OutOfBoundException);
  UniGaussian(const UniGaussian& other);
  UniGaussian& operator = (const UniGaussian& other);
  ~UniGaussian();

  double pdf(double f64X) const;
  double logpdf(double f64X) const;
  double KLDivergence(const UniGaussian& other) const;

  double getMean() const;
  double getVariance() const;
  void setMean(double f64Mean);
  void setVariance(double f64Variance) throw (OutOfBoundException);

protected:

};

#endif // UNIGAUSSIAN_H
