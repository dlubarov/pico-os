#pragma once

#include "../common.h"

class Blob
{
    void *m_buf_start;
    uint32 m_size;

  public:
    Blob() : m_buf_start(0), m_size(0) {}

    Blob(void *buf_start, uint32 size)
      : m_buf_start(buf_start), m_size(size) {}

    Blob(void *buf_start, void *buf_end)
      : m_buf_start(buf_start), m_size((size_t) buf_end - (size_t) buf_start) {}

    void *buf_start()
    {
      return m_buf_start;
    }

    uint32 size()
    {
      return m_size;
    }

    uint8 &operator[](size_t i) const
    {
      ASSERT(i >= 0, "negative blob index");
      ASSERT(i < m_size, "blob index out of range");
      return ((uint8 *) m_buf_start)[i];
    }
};
