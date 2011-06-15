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

#ifndef UNIDISTRIBUTION_H
#define UNIDISTRIBUTION_H

#include <iosfwd>

class UniDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const UniDistribution& obj);
  friend std::istream& operator >> (std::istream& stream, UniDistribution& obj);
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
