#ifndef OUTOFBOUNDEXCEPTION_H
#define OUTOFBOUNDEXCEPTION_H

#include <stdexcept>
#include <string>

class OutOfBoundException : public std::range_error {
  OutOfBoundException& operator = (const OutOfBoundException &other);

public:
  OutOfBoundException(const std::string &msg = "");
  OutOfBoundException(const OutOfBoundException &other);

protected:

};

#endif // OUTOFBOUNDEXCEPTION_H
