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

#ifndef SINGLETON_H
#define SINGLETON_H

#include "exceptions/InvalidOperationException.h"

template <class C> class Singleton {
public:
  Singleton() {
    if (instance)
      throw InvalidOperationException("Singleton(): Bad singleton instantiation");
    instance = (C*)this;
  };

  virtual ~Singleton() {
    instance = 0;
  };

  static C& getInstance() {
    if (!instance)
      new C();

    return *instance;
  };

  static bool exists() {
    return instance;
  };

protected:
  static C* instance;

};

template <class C> C* Singleton<C>::instance = 0;

#endif
