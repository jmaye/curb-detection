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

#include "functions/LogFactorialFunction.h"
#include "exceptions/BadArgumentException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

LogBinomialFunction::LogBinomialFunction() {
}

LogBinomialFunction::~LogBinomialFunction() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

double LogBinomialFunction::getValue(const VariableType&
    argument) const {
  LogFactorialFunction logFactorial;
  if (argument(0) >= argument(1))
    return logFactorial(argument(0)) - (logFactorial(argument(1)) +
      logFactorial(argument(0) - argument(1)));
  else
    throw BadArgumentException<VariableType>(argument,
      "LogBinomialFunction::getValue(): argument(0) must be larger than "
      "argument(1)",
      __FILE__, __LINE__);
}
