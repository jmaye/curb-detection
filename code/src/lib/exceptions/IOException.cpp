#include "IOException.h"

using namespace std;

IOException::IOException(const string &msg) : runtime_error(msg) {
}
