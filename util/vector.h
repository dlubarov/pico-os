#pragma once

#include "../common.h"
#include "deque.h"

template <class T>
class Vector
{
    Deque<T> storage;

  public:
    Vector() {}

    Vector(Vector &source)
    {
      panic("copy constructor not supported");
    }

    void push_back(const T x)
    {
      storage.push_back(x);
    }

    T pop_back()
    {
      return storage.pop_back();
    }

    T &operator[](size_t i) const
    {
      return storage[i];
    }

    size_t len() const
    {
      return storage.len();
    }
};
