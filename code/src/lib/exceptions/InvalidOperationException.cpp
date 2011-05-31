#include "exceptions/InvalidOperationException.h"

InvalidOperationException::InvalidOperationException(const std::string &msg) :
  std::runtime_error(msg) {
}
