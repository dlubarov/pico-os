#include "../common.h"
#include "hash.h"

class String
{
    size_t _len;
    char *buf;

  public:
    String()
      : _len(0),
        buf((char *) kmalloc(1))
    {
      buf[0] = 0;
    }

    String(const char *_buf)
      : _len(kstrlen(_buf)),
        buf((char *) kmalloc(_len + 1))
    {
      kmemcpy(buf, _buf, _len + 1);
      ASSERT(buf[_len] == 0, "string not terminated");
    }

    String(const String &s)
      : _len(s._len),
        buf((char *) kmalloc(s._len + 1))
    {
      kmemcpy(buf, s.buf, _len + 1);
      ASSERT(buf[_len] == 0, "string not terminated");
    }

    ~String()
    {
      kfree(buf);
    }

    size_t len() const
    {
      return _len;
    }

    const char *c_str() const
    {
      return buf;
    }

    bool operator==(String s) const
    {
      if (s._len != _len)
        return 0;
      for (size_t i = 0; i < _len; ++i)
        if (buf[i] != s.buf[i])
          return 0;
      return 1;
    }

    bool operator!=(String s) const
    {
      return !(*this == s);
    }

    String operator+(String s) const
    {
      size_t combined_len = _len + s._len;
      char *mem = (char *) kmalloc(combined_len + 1);
      kmemcpy(mem, buf, _len);
      kmemcpy(mem + _len, s.buf, s._len);
      mem[combined_len] = 0;
      String result(mem);
      kfree(mem);
      return result;
    }

    String operator+(const char *s) const
    {
      return *this + String(s);
    }

    String operator+(char c) const
    {
      char *mem = (char *) kmalloc(_len + 2);
      kmemcpy(mem, buf, _len);
      mem[_len] = c;
      mem[_len + 1] = 0;
      String result(mem);
      kfree(mem);
      return result;
    }

    unsigned int hash()
    {
      return hash_string(c_str());
    }
};
