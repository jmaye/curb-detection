#ifndef SINGLETON_H
#define SINGLETON_H

#include "exceptions/InvalidOperationException.h"

template <class C> class Singleton {
public:
  Singleton() {
    if (instance)
      throw InvalidOperationException("Singleton(): Bad singleton instantiation");
    instance = (C*)this;
  };

  virtual ~Singleton() {
    instance = 0;
  };

  static C& getInstance() {
    if (!instance)
      new C();

    return *instance;
  };

  static bool exists() {
    return instance;
  };

protected:
  static C* instance;

};

template <class C> C* Singleton<C>::instance = 0;

#endif
