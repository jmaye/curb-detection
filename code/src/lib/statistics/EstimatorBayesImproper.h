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

/** \file EstimatorBayesImproper.h
    \brief This file defines the EstimatorBayesImproper class, which implements
           Bayesian estimators with improper priors for various distributions
  */

#ifndef ESTIMATORBAYESIMPROPER_H
#define ESTIMATORBAYESIMPROPER_H

#include <cstdlib>

template <typename D> class EstimatorBayesImproper;

#include "statistics/EstimatorBayesImproperNormal1v.h"
#include "statistics/EstimatorBayesImproperNormalMv.h"

#endif // ESTIMATORBAYESIMPROPER
