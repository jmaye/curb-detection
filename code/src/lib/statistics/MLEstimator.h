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

/** \file Cell.h
    \brief This file defines the MLEstimator class, which implements the
           Maximum-Likelihood estimator for a univariate Gaussian
  */

#ifndef MLESTIMATOR_H
#define MLESTIMATOR_H

#include "statistics/UniGaussian.h"

#include <iosfwd>

#include <stdint.h>

/** The class MLEstimator implements the Maximum-Likelihood estimator for a
    univariate Gaussian
    \brief Maximum-Likelihood estimator for univariate Gaussian
  */
class MLEstimator {
  friend std::ostream& operator << (std::ostream& stream,
    const MLEstimator& obj);
  friend std::istream& operator >> (std::istream& stream, MLEstimator& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const MLEstimator& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, MLEstimator& obj);

  /** \name Streaming methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Private members
    @{
    */
  /// Number of points in the estimator
  uint32_t mu32PointsNbr;
  /// Hack for starting the estimator when variance will be 0
  bool mbStartRegular;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  MLEstimator();
  /// Copy constructor
  MLEstimator(const MLEstimator& other);
  /// Assignment operator
  MLEstimator& operator = (const MLEstimator& other);
  /// Destructor
  ~MLEstimator();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Adds a new point to the estimator
  void addDataPoint(UniGaussian& dist, double f64DataPoint);
  /// Returns the number of points in the estimator
  uint32_t getPointsNbr() const;
  /// Sets the number of points in the estimator
  void setPointsNbr(uint32_t u32PointsNbr);
  /** @}
    */

protected:

};

#endif // MLESTIMATOR_H
