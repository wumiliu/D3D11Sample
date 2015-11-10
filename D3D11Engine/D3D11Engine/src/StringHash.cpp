#include "StringHash.h"
#include <ctype.h>
/// Update a hash with the given 8-bit value using the SDBM algorithm.
inline unsigned SDBMHash(unsigned hash, unsigned char c) { return c + (hash << 6) + (hash << 16) - hash; }
/// Zero hash.
static const StringHash ZERO;

StringHash::StringHash() :
value_(0)
{
#ifdef _DEBUG
	m_strDebug = "";
#endif // _DEBUG
}
StringHash::StringHash(const StringHash& rhs) :
value_(rhs.value_)
{
#ifdef _DEBUG
	m_strDebug = rhs.m_strDebug;
#endif // _DEBUG
}
StringHash::StringHash(const char* str) :
value_(Calculate(str))
{
#ifdef _DEBUG
	m_strDebug = str;
#endif // _DEBUG
}
StringHash::StringHash(unsigned value) :
value_(value)
{
#ifdef _DEBUG
	m_strDebug = "";
#endif // _DEBUG
}

StringHash::StringHash(const std::string& str) :
value_(Calculate(str.c_str()))
{
#ifdef _DEBUG
	m_strDebug = str;
#endif // _DEBUG
}

unsigned StringHash::Calculate(const char* str)
{
	unsigned hash = 0;

	if (!str)
		return hash;

	while (*str)
	{
		// Perform the actual hashing as case-insensitive
		char c = *str;
		hash = SDBMHash(hash, (unsigned char)tolower(c));
		++str;
	}

	return hash;
}

