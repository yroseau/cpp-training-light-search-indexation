#pragma once

#include "Vector.h"
#include "String.h"

namespace ylib {

	template<class T>
	class Map
	{
		public:
			Map();
			Map(const Map<T>& m);
			~Map();

			inline const Vector<String> getKeys() const {
				return m_keys;
			}
			inline const Vector<T> getValues() const {
				return m_values;
			}

			Map<T>& add(String& key, T& value);
			Map<T>& add(const char *key, T& value);

			T* const getValue(String& key) const;
			T* const getValue(const char* key) const;

			inline T* const first() const {
				return m_values.get(0);
			}
			inline T* const last() const {
				return m_values.get(size() - 1);
			}

			Map<T>& removeKey(String& key);
			Map<T>& removeKey(const char* key);

			Map<T>& clear();
	
			inline size_t size() const {
				return m_keys.size();
			}

			Map<T>& operator=(Map<T> const& value);
			inline T* const operator[](String& key) const {
				return getValue(index);
			}
			inline T* const operator[](const char* key) const {
				return getValue(index);
			}

		protected:
			Vector<String> m_keys;
			Vector<T> m_values;
	};

};

#include "Map.cpp" // Need for template
