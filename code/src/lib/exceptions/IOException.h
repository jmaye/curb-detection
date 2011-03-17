#ifndef IOEXCEPTION_H
#define IOEXCEPTION_H

#include <stdexcept>
#include <string>

class IOException : public std::runtime_error {
  IOException& operator = (const IOException &other);

public:
  IOException(const std::string &msg = "");
  IOException(const IOException &other);

protected:

};

#endif // IOEXCEPTION_H
