#include "exceptions/OutOfBoundException.h"

OutOfBoundException::OutOfBoundException(const std::string &msg) :
  std::range_error(msg) {
}
