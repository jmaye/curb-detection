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

/** \file EstimatorBayesMixture.h
    \brief This file implements a batch Bayesian estimator for mixture
           distributions.
  */

#include "statistics/MixtureDistribution.h"
#include "statistics/DirichletDistribution.h"
#include "statistics/ConjugatePrior.h"
#include "utils/IsNumeric.h"
#include "utils/Not.h"
#include "functions/LogGammaFunction.h"
#include "functions/DigammaFunction.h"

/** The class EstimatorBayes is implemented for mixture distributions.
    \brief Mixture distributions Bayes estimator
  */
template <typename C, size_t M>
class EstimatorBayes<MixtureDistribution<C, M>,
    typename ConjugatePrior<C>::Result> :
  public virtual Serializable {
public:
  /** \name Traits
    @{
    */
  /// Specialization for scalar or vector input
  struct Traits {
  public:
    /// Get dimension of input data
    template <typename Z, typename IsNumeric<Z>::Result::Numeric>
      static size_t getDim(const typename C::RandomVariable& point);
    /// Get data at a given index
    template <typename Z, typename IsNumeric<Z>::Result::Numeric>
      static typename C::DomainType getData(const typename C::RandomVariable&
        point, size_t idx);
    /// Get dimension of input data
    template <typename Z, typename
        Not<typename IsNumeric<Z>::Result>::Result::Numeric>
      static size_t getDim(const typename C::RandomVariable& point);
    /// Get data at a given index
    template <typename Z, typename
        Not<typename IsNumeric<Z>::Result>::Result::Numeric>
      static typename C::DomainType getData(const typename C::RandomVariable&
        point, size_t idx);
  };
  /** @}
    */

  /** \name Types definitions
    @{
    */
  /// Point type
  typedef typename C::RandomVariable Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef typename Container::const_iterator ConstPointIterator;
  /// Alpha log-posterior
  class AlphaLogPdf :
    public Function<double, double> {
  public:
    /// Constructor with parameters
    AlphaLogPdf(size_t n, size_t k) :
        n(n),
        k(k) {
    }
    /// Copy constructor
    AlphaLogPdf(const AlphaLogPdf& other) :
      n(other.n),
      k(other.k) {
    }
    /// Assignment operator
    AlphaLogPdf& operator = (const AlphaLogPdf& other) {
      if (this != &other) {
        n = other.n;
        k = other.k;
      }
    }
    /// Returns logpdf of alpha posterior
    virtual double getValue(const double& argument) const {
      const LogGammaFunction<double> logGammaFunction;
      return (k - 1.5) * log(argument) - 1.0 / (2.0 * argument) +
        logGammaFunction(argument) - logGammaFunction(n + argument);
    }
    /// Number of points
    size_t n;
    /// Number of clusters
    size_t k;
  };
  /// Alpha log-posterior
  class AlphaLogPdfPrime :
    public Function<double, double> {
  public:
    /// Constructor with parameters
    AlphaLogPdfPrime(size_t n, size_t k) :
        n(n),
        k(k) {
    }
    /// Copy constructor
    AlphaLogPdfPrime(const AlphaLogPdfPrime& other) :
      n(other.n),
      k(other.k) {
    }
    /// Assignment operator
    AlphaLogPdfPrime& operator = (const AlphaLogPdfPrime& other) {
      if (this != &other) {
        n = other.n;
        k = other.k;
      }
    }
    /// Returns logpdfprime of alpha posterior
    virtual double getValue(const double& argument) const {
      const DigammaFunction<double> digammaFunction;
      return (k - 1.5) / argument + 1.0 / (2.0 * argument * argument) +
        digammaFunction(argument) - digammaFunction(n + argument);
    }
    /// Number of points
    size_t n;
    /// Number of clusters
    size_t k;
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with dirichlet prior
  EstimatorBayes(const DirichletDistribution<M>& dirPrior =
    DirichletDistribution<M>(), const typename
    ConjugatePrior<C>::Result& compPrior = ConjugatePrior<C>::Result(), size_t
    maxNumIter = 100);
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes& other);
  /// Assignment operator
  EstimatorBayes& operator = (const EstimatorBayes& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the assignments
  const Eigen::Matrix<int, Eigen::Dynamic, 1>& getAssignments() const;
  /// Returns the maximum number of iterations for Gibbs sampling
  size_t getMaxNumIter() const;
  /// Sets the maximum number of iterations for Gibbs sampling
  void setMaxNumIter(size_t maxNumIter);
  /// Add points to the estimator
  void addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd);
  /// Add points to the estimator using DP
  void addPointsDP(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd);
  /// Add points to the estimator
  void addPoints(const Container& points);
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
  /// Dirichlet prior
  DirichletDistribution<M> mDirPrior;
  /// Components prior
  typename ConjugatePrior<C>::Result mCompPrior;
  /// Maximum number of iterations for Gibbs sampling
  size_t mMaxNumIter;
  /// Assignments
  Eigen::Matrix<int, Eigen::Dynamic, 1> mAssignments;
  /** @}
    */

};

#include "statistics/EstimatorBayesMixture.tpp"
