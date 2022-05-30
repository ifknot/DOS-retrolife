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
#include "ptrdiff_t.h"
#include "null_ptr_t.h"

namespace jtl {

        template<typename T, size_t N>
        class data_vector {

        public:

// member types

            typedef T value_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type* pointer;
            typedef const value_type* const_pointer;
            typedef T* iterator;
            typedef const T* const_iterator;
            //reverse_iterator
            //const_reverse_iterator
            typedef T value_type;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
              
            // empty container constructor
            data_vector() : size_(0), capacity_(0) {} 

            // fill constructor
            data_vector(size_type n, const value_type& val = value_type()) : size_(n), capacity_(n) {
                assert(size_ <= N);
                for (size_type i = 0; i < size_; ++i) {
                    data_[i] = val;
                }
            }

            // range constructor
            template<typename InputIterator>
            data_vector(InputIterator first, InputIterator last) : size_(last - first), capacity_(last - first) {
                assert(size_ <= N);
                size_type i = 0;
                while (first < last) {

                }
            }

            //copy constructor
            data_vector(const data_vector& other) : size_(other.size()), capacity_(other.capacity()) {
                assert(size_ <= N);
                for (size_type i = 0; i < size_; ++i) data_[i] = other.data_[i];
            }

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

// capacity

            inline size_type size() const {
                return size_;
            }

            inline size_type max_size() const {
                return N;
            }

            // resize

            inline size_type capacity() {
                return capacity_;
            }

            inline bool empty() const {
                return size_ == 0;
            }

            // reserve

            // shrink_to_fit

// element access

            inline reference operator[](size_type pos) {
                return data_[pos];
            }

            inline const_reference operator[](size_type pos) const {
                return data_[pos];
            }

            //reference at(size_type n);

            //const_reference at(size_type n) const;

            inline reference front() {
                return data_[0];
            }

            inline const_reference front() const {
                return data_[0];
            }

            inline reference back() {
                return data_[size_ - 1];
            }

            inline const_reference back() const {
                return data_[size_ - 1];
            }

            inline const_pointer data() {
                return data_;
            }

// modifiers

            array& operator=(const array& other) {
                assert(size() == other.size());
                if (this != &other) {
                    for (size_type i = 0; i < size_; ++i) data_[i] = other.data_[i];
                }
                return *this;
            }

            inline void swap(array& other) {
                data_vector<T, N> temp_array = *this;
                *this = other;
                other = temp_array;
            }

// relational operators

            bool operator==(const data_vector& rhs) const {
                assert(size() == rhs.size());
                for (size_type i = 0; i < size(); ++i) {
                    if (data_[i] != rhs[i]) return false;
                }
                return true;
            }

            bool operator<(const data_vector& rhs) const {
                assert(size() == rhs.size());
                for (size_type i = 0; i < size(); ++i) {
                    if (data_[i] >= rhs[i]) return false;
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

        private:

            size_type size_;
            size_type capacity_;

            value_type data_[N];

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