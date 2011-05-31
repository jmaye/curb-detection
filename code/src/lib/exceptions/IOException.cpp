#include "exceptions/IOException.h"

IOException::IOException(const std::string &msg) :
  std::runtime_error(msg) {
}
