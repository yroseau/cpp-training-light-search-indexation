#include "String.h"

#include <string.h>
#include "utils.h"

namespace ylib {

	String::String() : m_data(nullptr)
	{

	}

	String::String(const String& s) : m_data(nullptr) {
		*this = s;
	}

	String::String(const char* c) : m_data(nullptr) {
		*this = c;
	}

	String::~String()
	{
		this->clear();
	}

	void String::clear() {
		SAFE_DELETE_ARRAY(m_data);
	}

	bool String::finishWith(const char* value) const {

		size_t len = length();
		size_t vLen = strlen(value);

		if (len < vLen) {
			return false;
		}

		const char* end = &m_data[len - vLen];

		return strcmp(end, value);

	}

	size_t String::length() const {
		if (m_data != nullptr) {
			return strlen(m_data);
		}
		return 0;
	}

	String& String::operator=(String const& s) {
		return *this = s.toCharArray();
	}

	String& String::operator=(const char* c) {
		clear(); 
		size_t len;
		if (c != nullptr && (len = strlen(c)) != 0) {
			m_data = new char[len + 1];
			strcpy(m_data, c);
		}
		return *this;
	}

	String& String::operator+=(String const& s) {
		return operator+=(s.toCharArray());
	}

	String& String::operator+=(const char* c) {
		size_t cLen;
		if (c == nullptr || (cLen = strlen(c)) == 0) {
			return *this;
		}
		size_t currentLen = length();
		size_t size = currentLen + cLen + 1;
		char* data = new char[size];
		strncpy(data, m_data, currentLen);
		strcpy(&data[currentLen], c);
		clear();
		m_data = data;
		return *this;
	}

	bool operator==(String const& a, String const& b) {
		return strcmp(a.toCharArray(), b.toCharArray()) == 0;
	}

	String operator+(String const& a, String const& b) {
		String result;
		result += a;
		result += b;
		return result;
	}

}
