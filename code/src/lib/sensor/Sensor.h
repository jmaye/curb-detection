#ifndef SENSOR_H
#define SENSOR_H

#include <iosfwd>

class Sensor {
  Sensor();

public:
  static double getNoise(double f64X, double f64Y, double f64Z);

protected:

};

#endif // SENSOR_H
