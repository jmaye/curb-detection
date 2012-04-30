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

#include "functions/FactorialFunction.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BinomialFunction::BinomialFunction() {
}

BinomialFunction::~BinomialFunction() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

size_t BinomialFunction::getValue(const VariableType& argument)
    const throw (BadArgumentException<VariableType>) {
  const FactorialFunction factorial;
  if (argument(0) >= argument(1))
    return factorial(argument(0)) / (factorial(argument(1)) *
      factorial(argument(0) - argument(1)));
  else
    throw BadArgumentException<VariableType>(argument,
      "BinomialFunction::getValue(): argument(0) must be larger than "
      "argument(1)",
      __FILE__, __LINE__);
}
