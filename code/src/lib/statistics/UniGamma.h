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

#ifndef UNIGAMMA_H
#define UNIGAMMA_H

#include "statistics/UniDistribution.h"
#include "exceptions/OutOfBoundException.h"

#include <iosfwd>

class UniGamma : public UniDistribution {
  friend std::ostream& operator << (std::ostream& stream, const UniGamma& obj);
  friend std::istream& operator >> (std::istream& stream, UniGamma& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const UniGamma& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, UniGamma& obj);

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
