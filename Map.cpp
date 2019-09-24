#include "utils.h"

namespace ylib {

	template<class T>
	Map<T>::Map() {

	}

	template<class T>
	Map<T>::Map(const Map<T>& m) {
		*this = m;
	}

	template<class T>
	Map<T>::~Map() {
		clear();
	}

	template<class T>
	Map<T>& Map<T>::clear() {
		m_keys.clear();
		m_values.clear();
		return *this;
	}

	template<class T>
	Map<T>& Map<T>::add(String& key, T& value) {
		m_keys.add(key);
		m_values.add(value);
		return *this;
	}

	template<class T>
	Map<T>& Map<T>::add(const char *key, T& value) {
		if (key != nullptr) {
			String _key(key);
			return add(_key, value);
		}
		return *this;
	}

	template<class T>
	T* const Map<T>::getValue(String& key) const {
		long i = m_keys.find(key);
		if (i == -1) {
			return nullptr;
		}
		return m_values[i];
	}

	template<class T>
	T* const Map<T>::getValue(const char* key) const {
		if (key == nullptr) {
			return nullptr;
		}
		return getValue(String(key));
	}

	template<class T>
	Map<T>& Map<T>::removeKey(String& key) {
		long i = m_keys.find(key);
		if (i != -1) {
		   m_keys.remove(i);
		   m_values.remove(i);
		}
		return *this;
	}

	template<class T>
	Map<T>& Map<T>::removeKey(const char* key) {
		if (key != nullptr) {
			String _key(key);
			return removeKey(_key);
		}
		return *this;
	}

	template<class T>
	Map<T>& Map<T>::operator=(Map<T> const& value) {
		clear();
		m_keys = value.getKeys();
		m_values = value.getValues();
		return *this;
	}

}
