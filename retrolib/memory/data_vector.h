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
#include <ostream>
#include <istream>

#include "size_t.h"
#include "null_ptr_t.h"

namespace jtl {

        template<typename T, size_t N>
        class data_vector {

        public:

            typedef T* iterator;
            typedef const T* const_iterator;

                

// iterators

            inline iterator begin() {
                    return data_;
            }

            inline const_iterator begin() const {
                    return data_;
            }

            inline iterator end() {
                    return data_ +  size_;
            }

            inline const_iterator end() const {
                    return data_ + size_;
            }

            inline size_type size() const {
                return size_;
            }

// element access

//non-manipulating operations

            bool operator==(const T rhs) const {
                    for (size_type i = 0; i < capacity(); ++i) {
                            if (data_[i] != rhs) return false;
                    }
                    return true;
            }

            bool operator!=(const T rhs) const {
                    for (size_type i = 0; i < capacity(); ++i) {
                            if (data_[i] != rhs) return true;
                    }
                    return false;
            }

            bool operator==(const data_vector& rhs) const {
                    assert(capacity() == rhs.capacity());
                    for (size_type i = 0; i < capacity(); ++i) {
                            if (data_[i] != rhs[i]) return false;
                    }
                    return true;
            }

            bool operator!=(const data_vector& rhs) const {
                    assert(capacity() == rhs.capacity());
                    for (size_type i = 0; i < capacity(); ++i) {
                            if (data_[i] != rhs[i]) return true;
                    }
                    return false;
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

        private:

                

        };

}

template<typename T, jtl::size_t N>
const jtl::data_vector<T, N> operator+ (const jtl::data_vector<T, N>& lhs, const jtl::data_vector<T, N>& rhs) {
        return jtl::data_vector<T, N>(lhs) += jtl::data_vector<T, N>(rhs);
}

template<typename T, jtl::size_t N>
const jtl::data_vector<T, N> operator- (const jtl::data_vector<T, N>& lhs, const jtl::data_vector<T, N>& rhs) {
        return jtl::data_vector<T, N>(lhs) -= jtl::data_vector<T, N>(rhs);
}

template<typename T, jtl::size_t N>
const jtl::data_vector<T, N> operator* (const jtl::data_vector<T, N>& lhs, const jtl::data_vector<T, N>& rhs) {
        return jtl::data_vector<T, N>(lhs) *= jtl::data_vector<T, N>(rhs);
}

template<typename T, jtl::size_t N>
const jtl::data_vector<T, N> operator/ (const jtl::data_vector<T, N>& lhs, const jtl::data_vector<T, N>& rhs) {
        return jtl::data_vector<T, N>(lhs) /= jtl::data_vector<T, N>(rhs);
}

template<typename T, jtl::size_t N>
std::ostream& operator<<(std::ostream& os, const jtl::data_vector<T, N>& a) {
    for (jtl::size_t i = 0; i < a.size(); ++i) {
        os << a[i] << ' ';
    }
    return os;
}

#endif