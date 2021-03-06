#pragma once

#include "../common.h"
#include "vector.h"
#include "pair.h"
#include "hash.h"

#define INITIAL_BUCKETS 1

// TODO: use static polymorphism
// http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern

template <class K, class V>
class HashMap
{
    unsigned int _len, num_buckets;
    Vector<Pair<K, V> > *buckets;

    void expand()
    {
      unsigned int old_num_buckets = num_buckets;
      Vector<Pair<K, V> > *old_buckets = buckets;
      num_buckets *= 2;
      buckets = new Vector<Pair<K, V> >[num_buckets];

      unsigned int i, j;
      for (i = 0; i < old_num_buckets; ++i)
      {
        Vector<Pair<K, V> > *b = &old_buckets[i];
        for (j = 0; j < b->len(); ++j)
          put((*b)[j].first, (*b)[j].second);
      }
      delete[] old_buckets;
    }

  protected:
    virtual unsigned int hash(K k) const = 0;

    virtual bool equal(K k1, K k2) const = 0;

  public:
    HashMap()
      : _len(0), num_buckets(INITIAL_BUCKETS),
        buckets(new Vector<Pair<K, V> >[INITIAL_BUCKETS]) {}

    HashMap(HashMap &source)
    {
      panic("copy constructor not supported");
    }

    ~HashMap()
    {
      delete[] buckets;
    }

    bool contains(K k) const
    {
      unsigned int i = hash(k) % num_buckets;
      Vector<Pair<K, V> > *b = buckets + i;
      for (i = 0; i < b->len(); ++i)
        if (equal((*b)[i].first, k))
          return 1;
      return 0;
    }

    V get(K k) const
    {
      unsigned int i = hash(k) % num_buckets;
      Vector<Pair<K, V> > *b = buckets + i;
      for (i = 0; i < b->len(); ++i)
      {
        Pair<K, V> p = (*b)[i];
        if (equal(p.first, k))
          return p.second;
      }
      panic("bad get()");
    }

    void put(K k, V v)
    {
      unsigned int i = hash(k) % num_buckets;
      Vector<Pair<K, V> > *b = buckets + i;
      for (i = 0; i < b->len(); ++i)
      {
        Pair<K, V> p = (*b)[i];
        if (equal(p.first, k))
        {
          p.second = v;
          return;
        }
      }
      Pair<K, V> p(k, v);
      b->push_back(p);
      if (++_len > num_buckets)
        expand();
    }

    V &operator[](K k)
    {
      if (contains(k))
      {
        unsigned int i = hash(k) % num_buckets;
        Vector<Pair<K, V> > *b = buckets + i;
        for (i = 0; i < b->len(); ++i)
          if (equal((*b)[i].first, k))
            return (*b)[i].second;
        ASSERT(0, "whoops in hashmap");
      }
      if (++_len > num_buckets)
        expand();
      unsigned int i = hash(k) % num_buckets;
      Vector<Pair<K, V> > *b = buckets + i;
      b->push_back(Pair<K, V>(k, V()));
      return b->back().second;
    }

    Vector<K> keys()
    {
      Vector<K> result;
      for (unsigned int i = 0; i < num_buckets; ++i)
      {
        Vector<Pair<K, V> > *bucket = buckets + i;
        for (unsigned int j = 0; j < bucket->len(); ++j)
          result.push_back((*bucket)[j].first);
      }
      return result;
    }

    unsigned int len() const
    {
      return _len;
    }
};

template <class V>
class StringHashMap : public HashMap<const char *, V>
{
  protected:
    virtual bool equal(const char *k1, const char *k2) const
    {
      return kstrcmp(k1, k2) == 0;
    }

    virtual unsigned int hash(const char *k) const
    {
      return hash_string(k);
    }
};

template <class V>
class UIntHashMap : public HashMap<unsigned int, V>
{
  protected:
    virtual bool equal(unsigned int a, unsigned int b) const
    {
      return a == b;
    }

    virtual unsigned int hash(unsigned int x) const
    {
      return x;
    }
};
