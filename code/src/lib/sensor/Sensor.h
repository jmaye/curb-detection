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

/** \file Sensor.h
    \brief This file defines the Sensor class, which represents the sensor
           characteristics
  */

#ifndef SENSOR_H
#define SENSOR_H

/** The class Sensor represents the sensor characteristics
    \brief Sensor characteristics
  */
class Sensor {
  /** \name Private constructor (not to be instantiated)
    @{
    */
  /// Default constructor
  Sensor();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Returns the sensor noise for a given position in space
  static double getNoise(double f64X, double f64Y, double f64Z);
  /** @}
    */

protected:

};

#endif // SENSOR_H
