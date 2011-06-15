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

#ifndef MLESTIMATOR_H
#define MLESTIMATOR_H

#include "statistics/UniGaussian.h"

#include <iosfwd>

#include <stdint.h>

class MLEstimator {
  friend std::ostream& operator << (std::ostream& stream,
    const MLEstimator& obj);
  friend std::istream& operator >> (std::istream& stream, MLEstimator& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const MLEstimator& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, MLEstimator& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  uint32_t mu32PointsNbr;
  bool mbStartRegular;

public:
  MLEstimator();
  MLEstimator(const MLEstimator& other);
  MLEstimator& operator = (const MLEstimator& other);
  ~MLEstimator();

  void addDataPoint(UniGaussian& dist, double f64DataPoint);

  uint32_t getPointsNbr() const;
  void setPointsNbr(uint32_t u32PointsNbr);

protected:

};

#endif // MLESTIMATOR_H
