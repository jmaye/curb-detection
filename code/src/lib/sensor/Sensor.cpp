#include "Sensor.h"

#include <iostream>
#include <fstream>

#include <math.h>

using namespace std;

double Sensor::getNoise(double f64X, double f64Y, double f64Z) {
  return (exp(0.001 * f64X) - 1);
}
