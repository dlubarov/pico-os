#pragma once

#include "../common.h"
#include "circularbuffer.h"

template <class T>
class Deque
{
    CircularBuffer<T> *buf;

    void expand()
    {
      CircularBuffer<T> *new_buf = new CircularBuffer<T>(buf->capacity() * 2);
      while (buf->len())
        new_buf->push_back(buf->pop_front());
      delete buf;
      buf = new_buf;
    }

  public:
    Deque() : buf(new CircularBuffer<T>(1)) {}

    Deque(Deque &source)
    {
      panic("copy constructor not supported");
    }

    ~Deque()
    {
      delete buf;
    }

    void push_front(const T x)
    {
      if (buf->full())
        expand();
      buf->push_front(x);
    }

    void push_back(const T x)
    {
      if (buf->full())
        expand();
      buf->push_back(x);
    }

    T pop_front()
    {
      // FIXME: shrink
      return buf->pop_front();
    }

    T pop_back()
    {
      // FIXME: shrink
      return buf->pop_back();
    }

    size_t len() const
    {
      return buf->len();
    }

    T &operator[](size_t i) const
    {
      ASSERT(i >= 0, "negative deque index");
      ASSERT(i < len(), "deque index out of range");
      return (*buf)[i];
    }
};
