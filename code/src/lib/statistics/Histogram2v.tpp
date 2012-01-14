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
Histogram<T, 2>::Histogram(const Eigen::Matrix<T, 2, 1>& minValue, const
  Eigen::Matrix<T, 2, 1>& maxValue, const Eigen::Matrix<T, 2, 1>& binWidth)
  throw (BadArgumentException<Eigen::Matrix<T, 2, 1> >) :
  mMinValue(minValue),
  mMaxValue(maxValue),
  mBinWidth(binWidth),
  mNormFactor(1.0) {
  if (minValue(0) >= maxValue(0) || minValue(1) >= maxValue(1))
    throw BadArgumentException<Eigen::Matrix<T, 2, 1> >(minValue,
      "Histogram<T, 2>::Histogram(): maximum value must be strictly larger "
      "than minimum value",
      __FILE__, __LINE__);
  if (binWidth(0) > maxValue(0) - minValue(0) ||
    binWidth(1) > maxValue(1) - minValue(1))
    throw BadArgumentException<Eigen::Matrix<T, 2, 1> >(binWidth,
      "Histogram<T, 2>::Histogram(): bin width must be strictly smaller than "
      "the considered interval",
    __FILE__, __LINE__);
  mNumBins = Traits<T>::computeNumBins(*this);
  mBins.resize(mNumBins(0), mNumBins(1));
  mBins.setConstant(0);
}

template <typename T>
Histogram<T, 2>::Histogram(const Histogram<T, 2>& other) :
  mMinValue(other.mMinValue),
  mMaxValue(other.mMaxValue),
  mBinWidth(other.mBinWidth),
  mNumBins(other.mNumBins),
  mBins(other.mBins),
  mNormFactor(other.mNormFactor) {
}

template <typename T>
Histogram<T, 2>& Histogram<T, 2>::operator =
  (const Histogram<T, 2>& other) {
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
Histogram<T, 2>::~Histogram() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T>
void Histogram<T, 2>::read(std::istream& stream) {
}

template <typename T>
void Histogram<T, 2>::write(std::ostream& stream) const {
  stream << "minimum value: " << std::endl << mMinValue << std::endl
    << "maximum value: " << std::endl << mMaxValue << std::endl
    << "bin width: " << std::endl << mBinWidth << std::endl
    << "number of bins: " << std::endl << mNumBins << std::endl
    << "bin content: " << std::endl << mBins << std::endl
    << "normalization factor: " << mNormFactor;
}

template <typename T>
void Histogram<T, 2>::read(std::ifstream& stream) {
}

template <typename T>
void Histogram<T, 2>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T>
const Eigen::Matrix<T, 2, 1>& Histogram<T, 2>::getMinValue() const {
  return mMinValue;
}

template <typename T>
const Eigen::Matrix<T, 2, 1>& Histogram<T, 2>::getMaxValue() const {
  return mMaxValue;
}

template <typename T>
const Eigen::Matrix<T, 2, 1>& Histogram<T, 2>::getBinWidth() const {
 return mBinWidth;
}

template <typename T>
const Eigen::Matrix<size_t, 2, 1>& Histogram<T, 2>::getNumBins() const {
  return mNumBins;
}

template <typename T>
const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>&
  Histogram<T, 2>::getBins() const {
  return mBins;
}

template <typename T>
void Histogram<T, 2>::setBinContent(const Eigen::Matrix<size_t, 2, 1>& bin,
  double value)
  throw (OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >) {
  if (bin(0) >= (size_t)mBins.rows() || bin(1) >= (size_t)mBins.cols())
    throw OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >(bin,
      "Histogram<T, 2>::setBinContent(): wrong bin number",
      __FILE__, __LINE__);
  mBins(bin(0), bin(1)) = value;
}

template <typename T>
double Histogram<T, 2>::getBinContent(const Eigen::Matrix<size_t, 2, 1>& bin)
  const throw (OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >) {
  if (bin(0) >= (size_t)mBins.rows() || bin(1) >= (size_t)mBins.cols())
    throw OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >(bin,
      "Histogram<T, 2>::getBinContent(): wrong bin number",
      __FILE__, __LINE__);
  return mBins(bin(0), bin(1));
}

template <typename T>
void Histogram<T, 2>::addBinContent(const Eigen::Matrix<size_t, 2, 1>& bin)
  throw (OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >) {
  if (bin(0) >= (size_t)mBins.rows() || bin(1) >= (size_t)mBins.cols())
    throw OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >(bin,
      "Histogram<T, 2>::addBinContent(): wrong bin number",
      __FILE__, __LINE__);
  mBins(bin(0), bin(1))++;
}

template <typename T>
double Histogram<T, 2>::getNormFactor() const {
  return mNormFactor;
}

template <typename T>
double Histogram<T, 2>::getBinsSum() const {
  return mBins.sum();
}

template <typename T>
double Histogram<T, 2>::getMaximumBinCount() const {
  return mBins.maxCoeff();
}

template <typename T>
Eigen::Matrix<size_t, 2, 1> Histogram<T, 2>::getMaximumBin() const {
  double max = mBins.maxCoeff();
  for (size_t i = 0; i < (size_t)mBins.rows(); ++i)
    for (size_t j = 0; j < (size_t)mBins.cols(); ++j)
      if (mBins(i, j) == max)
        return (Eigen::Matrix<size_t, 2, 1>() << i, j).finished();
  return Eigen::Matrix<size_t, 2, 1>::Zero();
}

template <typename T>
double Histogram<T, 2>::getMinimumBinCount() const {
  return mBins.minCoeff();
}

template <typename T>
Eigen::Matrix<size_t, 2, 1> Histogram<T, 2>::getMinimumBin() const {
  double min = mBins.minCoeff();
  for (size_t i = 0; i < (size_t)mBins.rows(); ++i)
    for (size_t j = 0; j < (size_t)mBins.cols(); ++j)
      if (mBins(i, j) == min)
        return (Eigen::Matrix<size_t, 2, 1>() << i, j).finished();
  return Eigen::Matrix<size_t, 2, 1>::Zero();
}

template <typename T>
Eigen::Matrix<double, 2, 1> Histogram<T, 2>::getSample() const {
  Histogram<T, 2> normHist(*this);
  normHist.normalize();
  Eigen::Matrix<double, Eigen::Dynamic, 1> cumProbabilities =
    Eigen::Matrix<double, Eigen::Dynamic, 1>::Zero(mBins.size() + 1, 1);
  double sum = 0.0;
  size_t idx = 1;
  for (size_t i = 0; i < (size_t)mBins.rows(); ++i) {
    for (size_t j = 0; j < (size_t)mBins.cols(); ++j) {
      sum += normHist.mBins(i, j);
      cumProbabilities(idx++) += sum;
    }
  }
  Randomizer<double> randomizer;
  double u = randomizer.sampleUniform();
  for (size_t i = 1; i < (size_t)cumProbabilities.size(); ++i) {
    if (u > cumProbabilities(i - 1) && u <= cumProbabilities(i)) {
      return getBinCenter((Eigen::Matrix<size_t, 2, 1>() << floor((i - 1) /
        (double)mBins.cols()), (i - 1) % mBins.cols()).finished());
    }
  }
  return getBinCenter((Eigen::Matrix<size_t, 2, 1>() << mBins.rows() - 1,
    mBins.cols() - 1).finished());
}

template <typename T>
Eigen::Matrix<double, 2, 1> Histogram<T, 2>::getSampleMean() const {
  if (mBins.sum()) {
    Eigen::Matrix<double, 2, 1> mean = Eigen::Matrix<double, 2, 1>::Zero();
    for (size_t i = 0; i < (size_t)mBins.rows(); ++i) {
      for (size_t j = 0; j < (size_t)mBins.cols(); ++j) {
        mean(0) += mBins(i, j) *
          getBinCenter((Eigen::Matrix<size_t, 2, 1>() << i, j).finished())(0);
        mean(1) += mBins(i, j) *
          getBinCenter((Eigen::Matrix<size_t, 2, 1>() << i, j).finished())(1);
      }
    }
    return mean / mBins.sum();
  }
  else
    return Eigen::Matrix<double, 2, 1>::
      Constant(std::numeric_limits<double>::quiet_NaN());
}

template <typename T>
void Histogram<T, 2>::clear() {
  mBins.setConstant(0);
}

template <typename T>
template <typename U, size_t D>
Eigen::Matrix<double, 2, 1> Histogram<T, 2>::Traits<U, D>::getBinCenter(const
  Histogram<U, 2>& hist, const Eigen::Matrix<size_t, 2, 1>& bin) {
  Eigen::Matrix<double, 2, 1> returnValue;
  if (hist.mBinWidth(0) == 1 && hist.mBinWidth(1) == 1) {
    returnValue(0) = hist.getBinStart(bin)(0);
    returnValue(1) = hist.getBinStart(bin)(1);
  }
  else {
    returnValue(0) = hist.getBinStart(bin)(0) + hist.mBinWidth(0) / 2.0;
    returnValue(1) = hist.getBinStart(bin)(1) + hist.mBinWidth(1) / 2.0;
  }
  return returnValue;
}

template <typename T>
template <size_t D>
Eigen::Matrix<double, 2, 1> Histogram<T, 2>::Traits<float, D>::getBinCenter(
  const Histogram<float, 2>& hist, const Eigen::Matrix<size_t, 2, 1>& bin) {
  Eigen::Matrix<double, 2, 1> returnValue;
  returnValue(0) = hist.getBinStart(bin)(0) + hist.mBinWidth(0) / 2.0;
  returnValue(1) = hist.getBinStart(bin)(1) + hist.mBinWidth(1) / 2.0;
  return returnValue;
}

template <typename T>
template <size_t D>
Eigen::Matrix<double, 2, 1> Histogram<T, 2>::Traits<double, D>::getBinCenter(
  const Histogram<double, 2>& hist, const Eigen::Matrix<size_t, 2, 1>& bin) {
  Eigen::Matrix<double, 2, 1> returnValue;
  returnValue(0) = hist.getBinStart(bin)(0) + hist.mBinWidth(0) / 2.0;
  returnValue(1) = hist.getBinStart(bin)(1) + hist.mBinWidth(1) / 2.0;
  return returnValue;
}

template <typename T>
Eigen::Matrix<double, 2, 1> Histogram<T, 2>::getBinCenter(const
  Eigen::Matrix<size_t, 2, 1>& bin) const
  throw (OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >) {
  if (bin(0) >= (size_t)mBins.rows() || bin(1) >= (size_t)mBins.cols())
    throw OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >(bin,
      "Histogram<T, 2>::getBinCenter(): wrong bin number",
      __FILE__, __LINE__);
  return Traits<T>::getBinCenter(*this, bin);
}

template <typename T>
Eigen::Matrix<T, 2, 1> Histogram<T, 2>::getBinStart(const
  Eigen::Matrix<size_t, 2, 1>& bin) const
  throw (OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >) {
  if (bin(0) >= (size_t)mBins.rows() || bin(1) >= (size_t)mBins.cols())
    throw OutOfBoundException<Eigen::Matrix<size_t, 2, 1> >(bin,
      "Histogram<T, 2>::getBinStart(): wrong bin number",
      __FILE__, __LINE__);
  Eigen::Matrix<T, 2, 1> returnValue;
  returnValue(0) = mMinValue(0) + bin(0) * mBinWidth(0);
  returnValue(1) = mMinValue(1) + bin(1) * mBinWidth(1);
  return returnValue;
}

template <typename T>
Eigen::Matrix<double, 2, 2> Histogram<T, 2>::getSampleCovariance() const {
  if (mBins.sum() > 1) {
    Eigen::Matrix<T, 2, 1> value = mMinValue;
    Eigen::Matrix<double, 2, 1> mean = getSampleMean();
    Eigen::Matrix<double, 2, 2> covariance =
      Eigen::Matrix<double, 2, 2>::Zero();
    for (size_t i = 0; i < (size_t)mBins.rows(); ++i) {
      value(1) = mMinValue(1);
      for (size_t j = 0; j < (size_t)mBins.cols(); ++j) {
        covariance(0, 0) += mBins(i, j) * (value(0) - mean(0)) * (value(0) -
          mean(0));
        covariance(0, 1) += mBins(i, j) * (value(0) - mean(0)) * (value(1) -
          mean(1));
        covariance(1, 0) += mBins(i, j) * (value(0) - mean(0)) * (value(1) -
          mean(1));
        covariance(1, 1) += mBins(i, j) * (value(1) - mean(1)) * (value(1) -
          mean(1));
        value(1) += mBinWidth(1);
      }
      value(0) += mBinWidth(0);
    }
    return covariance / (mBins.sum() - 1);
  }
  else
    return Eigen::Matrix<double, 2, 2>::
      Constant(std::numeric_limits<double>::quiet_NaN());
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T>
template <typename U, size_t D>
Eigen::Matrix<size_t, 2, 1> Histogram<T, 2>::Traits<U, D>::computeNumBins(const
  Histogram<U, 2>& hist) {
  return Eigen::Matrix<size_t, 2, 1>(floor((hist.mMaxValue(0) -
    hist.mMinValue(0)) / (double)hist.mBinWidth(0)) + 1,
    floor((hist.mMaxValue(1) - hist.mMinValue(1)) / (double)hist.mBinWidth(1)) +
    1);
}

template <typename T>
template <size_t D>
Eigen::Matrix<size_t, 2, 1> Histogram<T, 2>::Traits<float, D>::computeNumBins(
  const Histogram<float, 2>& hist) {
  return Eigen::Matrix<size_t, 2, 1>(ceil((hist.mMaxValue(0) -
    hist.mMinValue(0)) / hist.mBinWidth(0)),
    ceil((hist.mMaxValue(1) - hist.mMinValue(1)) / hist.mBinWidth(1)));
}

template <typename T>
template <size_t D>
Eigen::Matrix<size_t, 2, 1> Histogram<T, 2>::Traits<double, D>::computeNumBins(
  const Histogram<double, 2>& hist) {
  return Eigen::Matrix<size_t, 2, 1>(ceil((hist.mMaxValue(0) -
    hist.mMinValue(0)) / hist.mBinWidth(0)),
    ceil((hist.mMaxValue(1) - hist.mMinValue(1)) / hist.mBinWidth(1)));
}

template <typename T>
template <typename U, size_t D>
void Histogram<T, 2>::Traits<U, D>::addSample(Histogram<U, 2>& hist, const
  Eigen::Matrix<U, 2, 1>& sample) {
  if (sample(0) >= hist.mMinValue(0) && sample(0) <= hist.mMaxValue(0) &&
      sample(1) >= hist.mMinValue(1) && sample(1) <= hist.mMaxValue(1))
    hist.mBins((size_t)floor((sample(0) - hist.mMinValue(0)) /
      (double)hist.mBinWidth(0)), (size_t)floor((sample(1) -
      hist.mMinValue(1)) / (double)hist.mBinWidth(1)))++;
}

template <typename T>
template <size_t D>
void Histogram<T, 2>::Traits<float, D>::addSample(Histogram<float, 2>& hist,
  const Eigen::Matrix<float, 2, 1>& sample) {
  if (sample(0) >= hist.mMinValue(0) && sample(0) < hist.mMaxValue(0) &&
      sample(1) >= hist.mMinValue(1) && sample(1) < hist.mMaxValue(1))
    hist.mBins((size_t)floor((sample(0) - hist.mMinValue(0)) /
      hist.mBinWidth(0)), (size_t)floor((sample(1) - hist.mMinValue(1)) /
      hist.mBinWidth(1)))++;
}

template <typename T>
template <size_t D>
void Histogram<T, 2>::Traits<double, D>::addSample(Histogram<double, 2>& hist,
  const Eigen::Matrix<double, 2, 1>& sample) {
  if (sample(0) >= hist.mMinValue(0) && sample(0) < hist.mMaxValue(0) &&
      sample(1) >= hist.mMinValue(1) && sample(1) < hist.mMaxValue(1))
    hist.mBins((size_t)floor((sample(0) - hist.mMinValue(0)) /
      hist.mBinWidth(0)), (size_t)floor((sample(1) - hist.mMinValue(1)) /
      hist.mBinWidth(1)))++;
}

template <typename T>
void Histogram<T, 2>::addSample(const Eigen::Matrix<T, 2, 1>& sample) {
  Traits<T>::addSample(*this, sample);
}

template <typename T>
void Histogram<T, 2>::addSamples(const std::vector<Eigen::Matrix<T, 2, 1> >&
  samples) {
  for (size_t i = 0; i < samples.size(); ++i)
    addSample(samples[i]);
}

template <typename T>
void Histogram<T, 2>::normalize(double norm) {
  mNormFactor = norm;
  if (mBins.sum() != 0)
    scale(norm / (mBins.sum() * mBinWidth(0) * mBinWidth(1)));
}

template <typename T>
void Histogram<T, 2>::scale(double scale) {
  mBins *= scale;
}

template <typename T>
void Histogram<T, 2>::add(const Histogram<T, 2>& other) {
  mBins += other.mBins;
}
