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

#ifndef BAYESIANESTIMATOR_H
#define BAYESIANESTIMATOR_H

#include "statistics/UniGaussian.h"
#include "statistics/UniInverseGamma.h"

#include <iosfwd>

#include <stdint.h>

class BayesianEstimator {
  friend std::ostream& operator << (std::ostream& stream,
    const BayesianEstimator& obj);
  friend std::istream& operator >> (std::istream& stream,
    BayesianEstimator& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const BayesianEstimator& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    BayesianEstimator& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  uint32_t mu32PointsNbr;

public:
  BayesianEstimator();
  BayesianEstimator(const BayesianEstimator& other);
  BayesianEstimator& operator = (const BayesianEstimator& other);
  ~BayesianEstimator();

  void addDataPoint(UniGaussian& dist, UniGaussian& meanPrior,
    UniInverseGamma& variancePrior, double f64DataPoint);

  uint32_t getPointsNbr() const;
  void setPointsNbr(uint32_t u32PointsNbr);

protected:

};

#endif // BAYESIANESTIMATOR_H
