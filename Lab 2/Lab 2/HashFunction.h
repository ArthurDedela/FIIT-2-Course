#ifndef HASH_FUNCTION
#define HASH_FUNCTION

#include <string>

using std::string;

template <typename KEY>
class HashFunction
{
    size_t hash(const unsigned char *_First, size_t _Count) const
    {
        const size_t _FNV_offset_basis = 2166136261U;
        const size_t _FNV_prime = 16777619U;

        size_t _Val = _FNV_offset_basis;
        for (size_t _Next = 0; _Next < _Count; ++_Next)
        {
            _Val ^= (size_t)_First[_Next];
            _Val *= _FNV_prime;
        }
        return (_Val);
    }

public:
    size_t operator()(const KEY & v) const {
        return hash(reinterpret_cast<const unsigned char *>(&v), sizeof(v));
    }

};

template <>
class HashFunction<string>
{
    unsigned hash(const string & s) const
    {
        unsigned hash = 0;
        unsigned offset = 'a' - 1;
        for (auto c : s)
            hash = hash << 1 | (c - offset);

        return hash;
    }

public:

    unsigned operator()(const string & v) const {
        return hash(v);
    }
};

template <>
class HashFunction<int>
{
public:

    unsigned operator()(const int v) const {
        return v;
    }
};


#endif
