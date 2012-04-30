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

/** \file EstimatorBayes.h
    \brief This file defines the EstimatorBayes class, which implements Bayesian
           estimators for various distributions
  */

#ifndef ESTIMATORBAYES_H
#define ESTIMATORBAYES_H

#include <cstdlib>

#include "statistics/ConjugatePrior.h"

template <typename D, typename P = typename ConjugatePrior<D>::Result>
  class EstimatorBayes;

#include "statistics/EstimatorBayesNormal1v.h"
//#include "statistics/EstimatorBayesNormalMv.h"
//#include "statistics/EstimatorBayesMultinomial.h"
//#include "statistics/EstimatorBayesCategorical.h"
//#include "statistics/EstimatorBayesPoisson.h"
//#include "statistics/EstimatorBayesGeometric.h"
//#include "statistics/EstimatorBayesExponential.h"
//#include "statistics/EstimatorBayesMixture.h"

#endif // ESTIMATORBAYES_H
