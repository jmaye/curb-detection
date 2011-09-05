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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file Histogram2v.h
    \brief This file contains the definition of a bivariate histogram
  */

#ifndef HISTOGRAM2V_H
#define HISTOGRAM2V_H

#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"
#include "exceptions/OutOfBoundException.h"

#include <utils/SizeTSupport.h>

#include <vector>

/** The Histogram2v class defines bivariate histograms
    \brief 2-v histogram
  */
template <typename T> class Histogram<T, 2> :
  public virtual Serializable {
public:
  /** \name Traits
    @{
    */
  /// Computing for all integer types
  template <typename U, size_t D = 0> struct Traits {
  public:
    /// Bin computing function
    static Eigen::Matrix<size_t, 2, 1> computeNumBins(const Histogram<U, 2>&
      hist);
    /// Add sample to the histogram
    static void addSample(Histogram<U, 2>& hist, const Eigen::Matrix<U, 2, 1>&
      sample);
    /// Returns the value at the center of a bin
    static Eigen::Matrix<double, 2, 1> getBinCenter(const Histogram<U, 2>&
      hist, const Eigen::Matrix<size_t, 2, 1>& bin);
  };
  /// Computing for float type
  template <size_t D> struct Traits<float, D> {
  public:
    /// Bin computing function
    static Eigen::Matrix<size_t, 2, 1> computeNumBins(const Histogram<float, 2>&
      hist);
    /// Add sample to the histogram
    static void addSample(Histogram<float, 2>& hist, const
      Eigen::Matrix<float, 2, 1>& sample);
    /// Returns the value at the center of a bin
    static Eigen::Matrix<double, 2, 1> getBinCenter(const Histogram<float, 2>&
      hist, const Eigen::Matrix<size_t, 2, 1>& bin);
  };
  /// Computing for double type
  template <size_t D> struct Traits<double, D> {
  public:
    /// Bin computing function
    static Eigen::Matrix<size_t, 2, 1> computeNumBins(const
      Histogram<double, 2>& hist);
    /// Add sample to the histogram
    static void addSample(Histogram<double, 2>& hist,
      const Eigen::Matrix<double, 2, 1>& sample);
    /// Returns the value at the center of a bin
    static Eigen::Matrix<double, 2, 1> getBinCenter(const Histogram<double, 2>&
      hist, const Eigen::Matrix<size_t, 2, 1>& bin);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs histogram from parameters
  Histogram(const Eigen::Matrix<T, 2, 1>& minValue =
    Eigen::Matrix<T, 2, 1>::Zero(), const Eigen::Matrix<T, 2, 1>& maxValue =
    Eigen::Matrix<T, 2, 1>::Ones(), const Eigen::Matrix<T, 2, 1>& binWidth =
    Eigen::Matrix<T, 2, 1>::Ones())
    throw (BadArgumentException<Eigen::Matrix<T, 2, 1> >);
  /// Copy constructor
  Histogram(const Histogram<T, 2>& other);
  /// Assignment operator
  Histogram<T, 2>& operator = (const Histogram<T, 2>& other);
  /// Destructor
  virtual ~Histogram();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the minimum value of the histogram
  const Eigen::Matrix<T, 2, 1>& getMinValue() const;
  /// Returns the maximum value of the histogram
  const Eigen::Matrix<T, 2, 1>& getMaxValue() const;
  /// Returns the bin width of the histogram
  const Eigen::Matrix<T, 2, 1>& getBinWidth() const;
  /// Returns the number of bins of the histogram
  const Eigen::Matrix<size_t, 2, 1>& getNumBins() const;
  /// Returns the bins of the histogram
  const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>& getBins() const;
  /// Sets a bin content
  void setBinContent(const Eigen::Matrix<size_t, 2, 1>& bin, double value)
    throw (OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >);
  /// Returns a bin content
  double getBinContent(const Eigen::Matrix<size_t, 2, 1>& bin) const
    throw (OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >);
  /// Increment a bin
  void addBinContent(const Eigen::Matrix<size_t, 2, 1>& bin)
    throw (OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >);
  /// Returns the normalization factor
  double getNormFactor() const;
  /// Returns the bins sum
  double getBinsSum() const;
  /// Returns the maximum bin count of the histogram
  double getMaximumBinCount() const;
  /// Returns the maximum bin of the histogram
  Eigen::Matrix<size_t, 2, 1> getMaximumBin() const;
  /// Returns the minimum bin count of the histogram
  double getMinimumBinCount() const;
  /// Returns the minimum bin of the histogram
  Eigen::Matrix<size_t, 2, 1> getMinimumBin() const;
  /// Returns a sample from the histogram
  Eigen::Matrix<double, 2, 1> getSample() const;
  /// Returns the mean value of the histogram
  Eigen::Matrix<double, 2, 1> getSampleMean() const;
  /// Returns the covariance of the histogram
  Eigen::Matrix<double, 2, 2> getSampleCovariance() const;
  /// Clears the histogram
  void clear();
  /// Gets the value at the center of a bin
  Eigen::Matrix<double, 2, 1> getBinCenter(const Eigen::Matrix<size_t, 2, 1>&
    bin) const throw (OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >);
  /// Gets the value at the start of a bin
  Eigen::Matrix<T, 2, 1> getBinStart(const Eigen::Matrix<size_t, 2, 1>& bin)
    const throw (OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >);
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Add a sample to the histogram
  void addSample(const Eigen::Matrix<T, 2, 1>& sample);
  /// Add samples to the histogram
  void addSamples(const std::vector<Eigen::Matrix<T, 2, 1> >& samples);
  /// Normalize the histogram
  void normalize(double norm = 1.0);
  /// Scale the histogram
  void scale(double scale);
  /// Add another histogram
  void add(const Histogram<T, 2>& other);
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Minimum value to be stored
  Eigen::Matrix<T, 2, 1> mMinValue;
  /// Maximum value to be stored
  Eigen::Matrix<T, 2, 1> mMaxValue;
  /// Bin width
  Eigen::Matrix<T, 2, 1> mBinWidth;
  /// Number of bins
  Eigen::Matrix<size_t, 2, 1> mNumBins;
  /// Contains the bin values
  Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> mBins;
  /// Normalization factor
  double mNormFactor;
  /** @}
    */

};

#include "statistics/Histogram2v.tpp"

#endif // HISTOGRAM2V_H
