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

#include "statistics/Randomizer.h"

#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename T>
Histogram<T, 1>::Histogram(T minValue, T maxValue, T binWidth)
  throw (BadArgumentException<T>) :
  mMinValue(minValue),
  mMaxValue(maxValue),
  mBinWidth(binWidth),
  mNormFactor(1.0) {
  if (minValue >= maxValue)
    throw BadArgumentException<T>(minValue,
      "Histogram<T, 1>::Histogram(): maximum value must be strictly larger "
      "than minimum value",
      __FILE__, __LINE__);
  if (binWidth > maxValue - minValue)
    throw BadArgumentException<T>(binWidth,
      "Histogram<T, 1>::Histogram(): bin width must be strictly smaller than "
      "the considered interval",
    __FILE__, __LINE__);
  mNumBins = Traits<T>::computeNumBins(*this);
  mBins.resize(mNumBins);
  mBins.setConstant(0);
}

template <typename T>
Histogram<T, 1>::Histogram(const Histogram<T, 1>& other) :
  mMinValue(other.mMinValue),
  mMaxValue(other.mMaxValue),
  mBinWidth(other.mBinWidth),
  mNumBins(other.mNumBins),
  mBins(other.mBins),
  mNormFactor(other.mNormFactor) {
}

template <typename T>
Histogram<T, 1>& Histogram<T, 1>::operator =
  (const Histogram<T, 1>& other) {
  if (this != &other) {
    mMinValue = other.mMinValue;
    mMaxValue = other.mMaxValue;
    mBinWidth = other.mBinWidth;
    mNumBins = other.mNumBins;
    mBins = other.mBins;
    mNormFactor = other.mNormFactor;
  }
  return *this;
}

template <typename T>
Histogram<T, 1>::~Histogram() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T>
void Histogram<T, 1>::read(std::istream& stream) {
}

template <typename T>
void Histogram<T, 1>::write(std::ostream& stream) const {
  stream << "minimum value: " << mMinValue << std::endl
    << "maximum value: " << mMaxValue << std::endl
    << "bin width: " << mBinWidth << std::endl
    << "number of bins: " << mNumBins << std::endl
    << "bin content: " << std::endl << mBins << std::endl
    << "normalization factor: " << mNormFactor;
}

template <typename T>
void Histogram<T, 1>::read(std::ifstream& stream) {
}

template <typename T>
void Histogram<T, 1>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T>
T Histogram<T, 1>::getMinValue() const {
  return mMinValue;
}

template <typename T>
T Histogram<T, 1>::getMaxValue() const {
  return mMaxValue;
}

template <typename T>
T Histogram<T, 1>::getBinWidth() const {
 return mBinWidth;
}

template <typename T>
size_t Histogram<T, 1>::getNumBins() const {
  return mNumBins;
}

template <typename T>
const Eigen::Matrix<double, Eigen::Dynamic, 1>& Histogram<T, 1>::getBins()
  const {
  return mBins;
}

template <typename T>
void Histogram<T, 1>::setBinContent(size_t bin, double value)
  throw (OutOfBoundException<size_t>) {
  if (bin >= (size_t)mBins.size())
    throw OutOfBoundException<size_t>(bin,
      "Histogram<T, 1>::setBinContent(): wrong bin number",
      __FILE__, __LINE__);
  mBins(bin) = value;
}

template <typename T>
double Histogram<T, 1>::getBinContent(size_t bin) const 
  throw (OutOfBoundException<size_t>) {
  if (bin >= (size_t)mBins.size())
    throw OutOfBoundException<size_t>(bin,
      "Histogram<T, 1>::getBinContent(): wrong bin number",
      __FILE__, __LINE__);
  return mBins(bin);
}

template <typename T>
void Histogram<T, 1>::addBinContent(size_t bin)
  throw (OutOfBoundException<size_t>) {
  if (bin >= (size_t)mBins.size())
    throw OutOfBoundException<size_t>(bin,
      "Histogram<T, 1>::addBinContent(): wrong bin number",
      __FILE__, __LINE__);
  mBins(bin)++;
}

template <typename T>
double Histogram<T, 1>::getNormFactor() const {
  return mNormFactor;
}

template <typename T>
double Histogram<T, 1>::getBinsSum() const {
  return mBins.sum();
}

template <typename T>
double Histogram<T, 1>::getMaximumBinCount() const {
  return mBins.maxCoeff();
}

template <typename T>
size_t Histogram<T, 1>::getMaximumBin() const {
  double max = mBins.maxCoeff();
  for (size_t i = 0; i < (size_t)mBins.size(); ++i)
    if (mBins(i) == max)
      return i;
  return 0;
}

template <typename T>
double Histogram<T, 1>::getMinimumBinCount() const {
  return mBins.minCoeff();
}

template <typename T>
size_t Histogram<T, 1>::getMinimumBin() const {
  double min = mBins.minCoeff();
  for (size_t i = 0; i < (size_t)mBins.size(); ++i)
    if (mBins(i) == min)
      return i;
  return 0;
}

template <typename T>
double Histogram<T, 1>::getSample() const {
  Histogram<T, 1> normHist(*this);
  normHist.normalize();
  Eigen::Matrix<double, Eigen::Dynamic, 1> cumProbabilities =
    Eigen::Matrix<double, Eigen::Dynamic, 1>::Zero(mBins.size() + 1);
  double sum = 0.0;
  for (size_t i = 1; i < (size_t)mBins.size() + 1; ++i) {
    sum += normHist.mBins(i - 1);
    cumProbabilities(i) += sum;
  }
  Randomizer<double> randomizer;
  double u = randomizer.sampleUniform();
  for (size_t i = 1; i < (size_t)mBins.size() + 1; ++i)
    if (u > cumProbabilities(i - 1) && u <= cumProbabilities(i))
      return getBinCenter(i - 1);
  return getBinCenter(mBins.size() - 1);
}

template <typename T>
double Histogram<T, 1>::getSampleMean() const {
  if (mBins.sum()) {
    double mean = 0.0;
    for (size_t i = 0; i < (size_t)mBins.size(); ++i)
      mean += mBins(i) * getBinCenter(i);
    return mean / mBins.sum();
  }
  else
    return std::numeric_limits<double>::quiet_NaN();
}

template <typename T>
void Histogram<T, 1>::clear() {
  mBins.setConstant(0);
}

template <typename T>
template <typename U, size_t D>
double Histogram<T, 1>::Traits<U, D>::getBinCenter(const Histogram<U, 1>& hist,
  size_t bin) {
  if (hist.mBinWidth == 1)
    return hist.getBinStart(bin);
  else
    return hist.getBinStart(bin) + hist.mBinWidth / 2.0;
}

template <typename T>
template <size_t D>
double Histogram<T, 1>::Traits<float, D>::getBinCenter(const
  Histogram<float, 1>& hist, size_t bin) {
  return hist.getBinStart(bin) + hist.mBinWidth / 2.0;
}

template <typename T>
template <size_t D>
double Histogram<T, 1>::Traits<double, D>::getBinCenter(const
  Histogram<double, 1>& hist, size_t bin) {
  return hist.getBinStart(bin) + hist.mBinWidth / 2.0;
}

template <typename T>
double Histogram<T, 1>::getBinCenter(size_t bin) const
  throw (OutOfBoundException<size_t>) {
  if (bin >= (size_t)mBins.size())
    throw OutOfBoundException<size_t>(bin,
      "Histogram<T, 1>::getBinCenter(): wrong bin number",
      __FILE__, __LINE__);
  return Traits<T>::getBinCenter(*this, bin);
}

template <typename T>
T Histogram<T, 1>::getBinStart(size_t bin) const
  throw (OutOfBoundException<size_t>) {
  if (bin >= (size_t)mBins.size())
    throw OutOfBoundException<size_t>(bin,
      "Histogram<T, 1>::getBinStart(): wrong bin number",
      __FILE__, __LINE__);
  return mMinValue + bin * mBinWidth;
}

template <typename T>
double Histogram<T, 1>::getSampleVariance() const {
  if (mBins.sum()) {
    double mean = getSampleMean();
    double variance = 0.0;
    for (size_t i = 0; i < (size_t)mBins.size(); ++i) {
      variance += mBins(i) * (mean - getBinCenter(i)) *
        (mean - getBinCenter(i));
    }
    return variance / mBins.sum();
  }
  else
    return std::numeric_limits<double>::quiet_NaN();
}

template <typename T>
double Histogram<T, 1>::getSampleMedian() const {
  double binsSum = 0.0;
  for (size_t i = 0; i < (size_t)mBins.size(); ++i) {
    binsSum += mBins(i);
    if (binsSum > mBins.sum() / 2.0)
      return getBinCenter(i);
  }
  return 0;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T>
template <typename U, size_t D>
size_t Histogram<T, 1>::Traits<U, D>::computeNumBins(const Histogram<U, 1>&
  hist) {
  return (size_t)floor((hist.mMaxValue - hist.mMinValue) /
    (double)hist.mBinWidth) + 1;
}

template <typename T>
template <size_t D>
size_t Histogram<T, 1>::Traits<float, D>::computeNumBins(const
  Histogram<float, 1>& hist) {
  return (size_t)ceil((hist.mMaxValue - hist.mMinValue) / hist.mBinWidth);
}

template <typename T>
template <size_t D>
size_t Histogram<T, 1>::Traits<double, D>::computeNumBins(const
  Histogram<double, 1>& hist) {
  return (size_t)ceil((hist.mMaxValue - hist.mMinValue) / hist.mBinWidth);
}

template <typename T>
template <typename U, size_t D>
void Histogram<T, 1>::Traits<U, D>::addSample(Histogram<U, 1>& hist, U sample) {
  if (sample >= hist.mMinValue && sample <= hist.mMaxValue)
    hist.mBins((size_t)floor((sample - hist.mMinValue) /
      (double)hist.mBinWidth))++;
}

template <typename T>
template <size_t D>
void Histogram<T, 1>::Traits<float, D>::addSample(Histogram<float, 1>& hist,
  float sample) {
  if (sample >= hist.mMinValue && sample < hist.mMaxValue)
    hist.mBins((size_t)floor((sample - hist.mMinValue) / hist.mBinWidth))++;
}

template <typename T>
template <size_t D>
void Histogram<T, 1>::Traits<double, D>::addSample(Histogram<double, 1>& hist,
  double sample) {
  if (sample >= hist.mMinValue && sample < hist.mMaxValue)
    hist.mBins((size_t)floor((sample - hist.mMinValue) / hist.mBinWidth))++;
}


template <typename T>
void Histogram<T, 1>::addSample(T sample) {
  Traits<T>::addSample(*this, sample);
}

template <typename T>
void Histogram<T, 1>::addSamples(const std::vector<T>& samples) {
  for (size_t i = 0; i < samples.size(); ++i)
    addSample(samples[i]);
}

template <typename T>
void Histogram<T, 1>::normalize(double norm) {
  mNormFactor = norm;
  if (mBins.sum() != 0)
    scale(norm / (mBins.sum() * mBinWidth));
}

template <typename T>
void Histogram<T, 1>::scale(double scale) {
  mBins *= scale;
}

template <typename T>
void Histogram<T, 1>::add(const Histogram<T, 1>& other) {
  mBins += other.mBins;
}
