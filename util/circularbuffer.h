#pragma once

#include "../common.h"

template <class T>
class CircularBuffer
{
    size_t _len;
    const size_t _capacity;
    T *start, *end;
    T * const buf;

  public:
    CircularBuffer(size_t __capacity)
      : _len(0), _capacity(__capacity),
        buf((T *) kmalloc(__capacity * sizeof(T))) {
      start = end = buf;
    }

    CircularBuffer(CircularBuffer &source)
    {
      panic("copy constructor not supported");
    }

    ~CircularBuffer()
    {
      kfree(buf);
    }

    T &front()
    {
      return *start;
    }

    T &back()
    {
      T *p = end - 1;
      if (p < buf)
        p += _capacity;
      return *p;
    }

    void push_front(const T x)
    {
      if (--start < buf)
        start += _capacity;
      *start = x;
      ++_len;
    }

    void push_back(const T x)
    {
      *end = x;
      if (++end == buf + _capacity)
        end = buf;
      ++_len;
    }

    T pop_front()
    {
      T x = *start;
      if (++start == buf + _capacity)
        start = buf;
      --_len;
      return x;
    }

    T pop_back()
    {
      if (--end < buf)
        end += _capacity;
      --_len;
      return *end;
    }

    T &operator[](size_t i) const
    {
      T *p = start + i;
      if (p >= buf + _capacity)
        p -= _capacity;
      return *p;
    }

    int len() const
    {
      return _len;
    }

    int capacity() const
    {
      return _capacity;
    }

    bool empty() const
    {
      return _len == 0;
    }

    bool full() const
    {
      return _len == _capacity;
    }
};
