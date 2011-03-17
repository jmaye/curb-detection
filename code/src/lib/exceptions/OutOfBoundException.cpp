#include "OutOfBoundException.h"

using namespace std;

OutOfBoundException::OutOfBoundException(const string &msg)
  : range_error(msg) {
}
