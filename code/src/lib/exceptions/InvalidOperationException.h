#ifndef INVALIDOPERATIONEXCEPTION_H
#define INVALIDOPERATIONEXCEPTION_H

#include <stdexcept>
#include <string>

class InvalidOperationException : public std::runtime_error {
  InvalidOperationException& operator =
  (const InvalidOperationException &other);

public:
  InvalidOperationException(const std::string &msg = "");
  InvalidOperationException(const InvalidOperationException &other);

protected:

};

#endif // INVALIDOPERATIONEXCEPTION_H
