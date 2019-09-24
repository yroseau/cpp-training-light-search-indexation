#pragma once

#include "types.h"

namespace ylib
{

	class String
	{
		public:
			String();
			String(const String& s);
			String(const char* c);
			~String();

			size_t length() const;
			void clear();

			inline const char* const toCharArray() const {
				return m_data == nullptr ? "" : m_data;
			}

			bool finishWith(const char*) const;

			String& operator=(String const& s);
			String& operator=(const char* c);
			String& operator+=(String const& s);
			String& operator+=(const char* c);

		protected:
			char* m_data; // @todo use wchar_t
	};

	bool operator==(String const& a, String const& b);
	String operator+(String const& a, String const& b);

}
