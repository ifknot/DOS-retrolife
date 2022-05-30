/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      29.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef DATA_VECTOR_H
#define DATA_VECTOR_H

#include <cassert>

#include "../memory/array.h"

namespace jtl {

	template<typename T, size_t N>
	struct data_vector : public array<T, N> {
		
		data_vector() : array() {}

		data_vector(array<T, N> other) {
			assert(capacity() == other.capacity());
			for (size_type i = 0; i < capacity(); ++i) {
				data_[i] = other[i];
			}
		}
		
//non-manipulating operations

		bool operator==(const T rhs) const {
			for (size_type i = 0; i < capacity(); ++i) {
				if (data_[i] != rhs) return false;
			}
			return true;
		}

		bool operator==(const data_vector& rhs) const {
			assert(capacity() == rhs.capacity());
			for (size_type i = 0; i < capacity(); ++i) {
				if (data_[i] != rhs[i]) return false;
			}
			return true;
		}

//manipulating operations

		data_vector& operator+=(const T rhs) {
			for (size_type i = 0; i < capacity(); ++i) {
				data_[i] += rhs;
			}
			return *this;
		}

		data_vector& operator+=(const data_vector& rhs) {
			assert(capacity() == rhs.capacity());
			for (size_type i = 0; i < capacity(); ++i) {
				data_[i] += rhs[i];
			}
			return *this;
		}

		data_vector& operator-=(const T rhs) {
			for (size_type i = 0; i < capacity(); ++i) {
				data_[i] -= rhs;
			}
			return *this;
		}

		data_vector& operator-=(const data_vector& rhs) {
			assert(capacity() == rhs.capacity());
			for (size_type i = 0; i < capacity(); ++i) {
				data_[i] -= rhs[i];
			}
			return *this;
		}

		data_vector& operator*=(const T rhs) {
			for (size_type i = 0; i < capacity(); ++i) {
				data_[i] *= rhs;
			}
			return *this;
		}

		data_vector& operator*=(const data_vector& rhs) {
			assert(capacity() == rhs.capacity());
			for (size_type i = 0; i < capacity(); ++i) {
				data_[i] *= rhs[i];
			}
			return *this;
		}

		data_vector& operator/=(const T rhs) {
			for (size_type i = 0; i < capacity(); ++i) {
				data_[i] /= rhs;
			}
			return *this;
		}

		data_vector& operator/=(const data_vector& rhs) {
			assert(capacity() == rhs.capacity());
			for (size_type i = 0; i < capacity(); ++i) {
				data_[i] /= rhs[i];
			}
			return *this;
		}
	
	};

}

template<typename T, jtl::size_t N>
const jtl::data_vector<T, N> operator+ (const jtl::data_vector<T, N>& lhs, const jtl::data_vector<T, N>& rhs) {
	return jtl::data_vector<T, N>(lhs) += jtl::data_vector<T, N>(rhs);
}


#endif