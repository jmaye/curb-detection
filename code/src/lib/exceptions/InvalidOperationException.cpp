#include "InvalidOperationException.h"

using namespace std;

InvalidOperationException::InvalidOperationException(const string &msg)
  : runtime_error(msg) {
}
