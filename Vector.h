#pragma once

#include "types.h"

namespace ylib
{

	template<class T>
	class Vector
	{
		public:
			Vector();
			Vector(const Vector<T>& v);
			~Vector();

			inline size_t size() const {
				return m_size;
			}
			void clear();

			Vector& add(T value);
			Vector& remove(size_t index);

			usize_t find(T const& value) const;
			inline T* const get(size_t index) const {
				return index >= m_size || index < 0 ? nullptr : m_values[index];
			}
			inline T* const first() const {
				return get(0);
			}
			inline T* const last() const {
				return get(m_size - 1);
			}
			inline const T* const values() const {
				return *m_values;
			}

			Vector& mergeUnique(Vector<T> const& value);
			Vector& merge(Vector<T> const& value);

			Vector& operator=(Vector<T> const& value);
			Vector& operator+=(Vector<T> const& value);
			Vector& operator+=(T const& value);
			inline T* const operator[](size_t index) const {
				return get(index);
			}

		protected:
			T** m_values;
			size_t m_size;
	};

}

#include "Vector.cpp" // need for template
