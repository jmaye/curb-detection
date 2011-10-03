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

/** \file EstimatorMLNormal1v.h
    \brief This file implements an ML estimator for univariate normal
           distributions.
  */

#include "statistics/NormalDistribution.h"
#include "base/Serializable.h"

#include <vector>

/** The class EstimatorML is implemented for univariate normal distributions.
    \brief Univariate normal distribution ML estimator
  */
template <> class EstimatorML<NormalDistribution<1> > :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef double Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  inline EstimatorML();
  /// Copy constructor
  inline EstimatorML(const EstimatorML<NormalDistribution<1> >& other);
  /// Assignment operator
  inline EstimatorML<NormalDistribution<1> >& operator =
    (const EstimatorML<NormalDistribution<1> >& other);
  /// Destructor
  inline virtual ~EstimatorML();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the number of points
  inline size_t getNumPoints() const;
  /// Returns the validity state of the estimator
  inline bool getValid() const;
  /// Returns the estimated mean
  inline double getMean() const;
  /// Returns the estimated variance
  inline double getVariance() const;
  /// Add a point to the estimator
  inline void addPoint(const Point& point);
  /// Add points to the estimator
  inline void addPoints(const ConstPointIterator& itStart, const
    ConstPointIterator& itEnd);
  /// Reset the estimator
  inline void reset();
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  inline virtual void read(std::istream& stream);
  /// Writes to standard output
  inline virtual void write(std::ostream& stream) const;
  /// Reads from a file
  inline virtual void read(std::ifstream& stream);
  /// Writes to a file
  inline virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Estimated mean
  double mMean;
  /// Estimated variance
  double mVariance;
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /** @}
    */

};

#include "statistics/EstimatorMLNormal1v.tpp"
