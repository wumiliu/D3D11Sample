#pragma once
#include <string>
class StringHash
{
public:
	/// Construct with zero value.
	StringHash();
	/// Copy-construct from another hash.
	StringHash(const StringHash& rhs);

	/// Construct with an initial value.
	explicit StringHash(unsigned value);
	/// Construct from a C string case-insensitively.
	StringHash(const char* str);
	StringHash(const std::string& str);


	// Test for equality with another hash.
	bool operator ==(const StringHash& rhs) const { return value_ == rhs.value_; }
	/// Test for inequality with another hash.
	bool operator !=(const StringHash& rhs) const { return value_ != rhs.value_; }

	/// Return hash value.
	unsigned Value() const { return value_; }
	/// Return hash value for HashSet & HashMap.
	unsigned ToHash() const { return value_; }
	operator unsigned()const{ return value_; }
	/// Calculate hash value case-insensitively from a C string.
	static unsigned Calculate(const char* str);
	/// Zero hash.
	static const StringHash ZERO;

private:
	/// Hash value.
	unsigned value_;
public:
#ifdef _DEBUG
	std::string m_strDebug;
#endif // _DEBUG
};

