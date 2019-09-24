/**
 *
 * Template file
 * @see Vector.h
 *
 */

#include "utils.h"
#include <string.h>

namespace ylib
{

	template<class T>
	Vector<T>::Vector() : m_values(nullptr), m_size(0) {

	}

	template<class T>
	Vector<T>::Vector(const Vector<T>& v) : m_values(nullptr), m_size(0) {
		*this = v;
	}

	template<class T>
	Vector<T>::~Vector() {
		clear();
	}

	template<class T>
	void Vector<T>::clear() {
		SAFE_DELETE_ARRAY(m_values);
		m_size = 0;
	}

	template<class T>
	Vector<T>& Vector<T>::add(T value) {
		T** _values = new T*[m_size + 1];
		memcpy(_values, m_values, sizeof(T*)*m_size);
		_values[m_size] = new T(value);
		SAFE_DELETE_ARRAY(m_values);
		m_values = _values;
		++m_size;
		return *this;
	}

	template<class T>
	Vector<T>& Vector<T>::remove(size_t index) {
		if (index >= m_size) {
			// invalid index
			return *this;
		}
		if (m_size == 1) {
			clear();
			return *this;
		}
		T** _values = new T*[m_size - 1];
		int _i = 0;
		for (size_t i = 0; i != m_size; ++i) {
			if (i != index) {
				_values[_i++] = new T(*m_values[i]);
			}
			else {
				SAFE_DELETE(m_values[i]);
			}
		}
		m_values = _values;
		--m_size;
		return *this;
	}

	template<class T>
	usize_t Vector<T>::find(T const& value) const {
		for (size_t i = 0; i != m_size; ++i) {
			if (m_values[i] != nullptr && *m_values[i] == value) {
				return static_cast<usize_t>(i);
			}
		}
		return -1;
	}

	template<class T>
	Vector<T>&  Vector<T>::operator=(Vector<T> const& value) {
		clear(); 
		for (size_t i = 0; i != value.size(); ++i) {
			add(*value.get(i));
		}
		return *this;
	}

	template<class T>
	Vector<T>& Vector<T>::mergeUnique(Vector<T> const& value) {
		for (int i = 0; i != value.size(); ++i) {
			if (find(*value[i]) == -1) {
				add(*value[i]);
			}
		}
		return *this;
	}

	template<class T>
	Vector<T>& Vector<T>::merge(Vector<T> const& value) {
		for (int i = 0; i != value.size(); ++i) {
			add(*value[i]);
		}
		return *this;
	}

	template<class T>
	Vector<T>& Vector<T>::operator+=(Vector<T> const& value) {
		return merge(value);
	}

	template<class T>
	Vector<T>& Vector<T>::operator+=(T const& value) {
		return add(value);
	}

}
