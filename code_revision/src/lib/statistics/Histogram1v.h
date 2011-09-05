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

/** \file Histogram1v.h
    \brief This file contains the definition of an univariate histogram
  */

#ifndef HISTOGRAM1V_H
#define HISTOGRAM1V_H

#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"
#include "exceptions/OutOfBoundException.h"

#include <Eigen/Core>

#include <vector>

template <typename T, size_t M = 1> class Histogram;

/** The Histogram1v class defines univariate histograms
    \brief 1-v histogram
  */
template <typename T> class Histogram<T, 1> :
  public virtual Serializable {
public:
  /** \name Traits
    @{
    */
  /// Computing for all integer types
  template <typename U, size_t D = 0> struct Traits {
  public:
    /// Bin computing function
    static size_t computeNumBins(const Histogram<U, 1>& hist);
    /// Add sample to the histogram
    static void addSample(Histogram<U, 1>& hist, U sample);
    /// Returns the value at the center of a bin
    static double getBinCenter(const Histogram<U, 1>& hist, size_t bin);
  };
  /// Computing for float type
  template <size_t D> struct Traits<float, D> {
  public:
    /// Bin computing function
    static size_t computeNumBins(const Histogram<float, 1>& hist);
    /// Add sample to the histogram
    static void addSample(Histogram<float, 1>& hist, float sample);
    /// Returns the value at the center of a bin
    static double getBinCenter(const Histogram<float, 1>& hist, size_t bin);
  };
  /// Computing for double type
  template <size_t D> struct Traits<double, D> {
  public:
    /// Bin computing function
    static size_t computeNumBins(const Histogram<double, 1>& hist);
    /// Add sample to the histogram
    static void addSample(Histogram<double, 1>& hist, double sample);
    /// Returns the value at the center of a bin
    static double getBinCenter(const Histogram<double, 1>& hist, size_t bin);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs histogram from parameters
  Histogram(T minValue = T(0), T maxValue = T(1), T binWidth = T(1))
    throw (BadArgumentException<T>);
  /// Copy constructor
  Histogram(const Histogram<T, 1>& other);
  /// Assignment operator
  Histogram<T, 1>& operator = (const Histogram<T, 1>& other);
  /// Destructor
  virtual ~Histogram();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the minimum value of the histogram
  T getMinValue() const;
  /// Returns the maximum value of the histogram
  T getMaxValue() const;
  /// Returns the bin width of the histogram
  T getBinWidth() const;
  /// Returns the number of bins of the histogram
  size_t getNumBins() const;
  /// Returns the bins of the histogram
  const Eigen::Matrix<double, Eigen::Dynamic, 1>& getBins() const;
  /// Sets a bin content
  void setBinContent(size_t bin, double value)
    throw (OutOfBoundException<size_t>);
  /// Returns a bin content
  double getBinContent(size_t bin) const throw (OutOfBoundException<size_t>);
  /// Increment a bin
  void addBinContent(size_t bin) throw (OutOfBoundException<size_t>);
  /// Returns the normalization factor
  double getNormFactor() const;
  /// Returns the bins sum
  double getBinsSum() const;
  /// Returns the maximum bin count of the histogram
  double getMaximumBinCount() const;
  /// Returns the maximum bin of the histogram
  size_t getMaximumBin() const;
  /// Returns the minimum bin count of the histogram
  double getMinimumBinCount() const;
  /// Returns the minimum bin of the histogram
  size_t getMinimumBin() const;
  /// Returns a sample from the histogram
  double getSample() const;
  /// Returns the mean value of the histogram
  double getSampleMean() const;
  /// Returns the variance of the histogram
  double getSampleVariance() const;
  /// Returns the median of the histogram
  double getSampleMedian() const;
  /// Clears the histogram
  void clear();
  /// Gets the x value at the center of a bin
  double getBinCenter(size_t bin) const throw (OutOfBoundException<size_t>);
  /// Gets the x value at the start of a bin
  T getBinStart(size_t bin) const throw (OutOfBoundException<size_t>);
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Add a sample to the histogram
  void addSample(T sample);
  /// Add samples to the histogram
  void addSamples(const std::vector<T>& samples);
  /// Normalize the histogram
  void normalize(double norm = 1.0);
  /// Scale the histogram
  void scale(double scale);
  /// Add another histogram
  void add(const Histogram<T, 1>& other);
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
  T mMinValue;
  /// Maximum value to be stored
  T mMaxValue;
  /// Bin width
  T mBinWidth;
  /// Number of bins
  size_t mNumBins;
  /// Contains the bin values
  Eigen::Matrix<double, Eigen::Dynamic, 1> mBins;
  /// Normalization factor
  double mNormFactor;
  /** @}
    */

};

#include "statistics/Histogram1v.tpp"

#endif // HISTOGRAM1V_H
