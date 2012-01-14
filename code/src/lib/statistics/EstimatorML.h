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

/** \file EstimatorML.h
    \brief This file defines the EstimatorML class, which implements
           maximum likelihood estimators for various distributions
  */

#ifndef ESTIMATORML_H
#define ESTIMATORML_H

#include <cstdlib>

template <typename D, size_t M = 1, size_t N = 1> class EstimatorML;

#include "statistics/EstimatorMLNormal1v.h"
#include "statistics/EstimatorMLNormalMv.h"
#include "statistics/EstimatorMLCategorical.h"
#include "statistics/EstimatorMLMultinomial.h"
#include "statistics/EstimatorMLExponential.h"
#include "statistics/EstimatorMLGeometric.h"
#include "statistics/EstimatorMLPoisson.h"
#include "statistics/EstimatorMLLinearRegression.h"
#include "statistics/EstimatorMLMixtureLinearRegression.h"
#include "statistics/EstimatorMLMixtureNormal1v.h"
#include "statistics/EstimatorMLMixtureNormalMv.h"

#endif // ESTIMATORML
