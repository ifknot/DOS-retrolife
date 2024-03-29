
/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      29.05.2022
 *  @copyright � Jeremy Thornton, 2022. All right reserved.
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

#define DATA_VECTOR_MAX_SIZE 0xFFFF

namespace jtl {

        template<typename T, size_t N = 256>
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
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;

// construction

            // empty container constructor
            data_vector() :
                size_(0),
                capacity_(N),
                data_(new T[N])
            {}

            // fill constructor
            explicit data_vector(size_type n, const value_type val = value_type(), bool f = true) :
                size_(n),
                capacity_(N),
                data_(new T[N])
            {
                assert(size_ <= N && f);
                while (n) {
                    data_[--n] = val;
                }
            }

            // range constructor
            template<typename InputIterator>
            data_vector(InputIterator first, const InputIterator last) :
                size_(last - first),
                capacity_(N),
                data_(new T[N])
            {
                assert(size_ <= N);
                size_type i = 0;
                while (first < last) {
                    data_[i++] = *first++;
                }
            }

            // copy constructor
            data_vector(const data_vector& other) :
                size_(other.size()),
                capacity_(other.capacity()),
                data_(new T[N])
            {
                assert(capacity_ <= N);
                assert(size_ <= N);
                for (size_type i = 0; i < size_; ++i) data_[i] = other.data_[i];
            }

            // destructor
            ~data_vector() {
                delete[] data_;
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

            static inline size_type max_size() {
                return DATA_VECTOR_MAX_SIZE / sizeof(value_type);
            }

            void resize(size_type n) { // TODO: n > N
                assert(n <= N);
                size_ = n;
            }

            static inline size_type capacity() {
                return N;
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

            inline pointer data() {
                return data_;
            }

            inline const_pointer data() const {
                return data_;
            }

// modifiers

            data_vector& operator=(const data_vector& other) {
                assert(capacity() >= other.size());
                if (this != &other) {
                    size_ = other.size();
                    for (size_type i = 0; i < size_; ++i) {
                        data_[i] = other.data_[i];
                    }
                }
                return *this;
            }

            // asign

            void push_back(const value_type& val) {
                ++size_;
                assert(size_ <= N);
                back() = val;
            }

            void pop_back() {
                assert(size_ > 0);
                --size_;
            }

            // insert

            // erase

            inline void swap(data_vector& other) {
                data_vector<T, N> temp_data_vector = *this;
                *this = other;
                other = temp_data_vector;
            }

            void clear() {
                size_ = 0;
            }

            // emplace

            // emplace_back

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

// ordering operations

            // sort

            // shuffle

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

// serialisation

            std::ostream& write(std::ostream& os) const {
                for (size_type i = 0; i < size(); ++i) {
                    os << data_[i] << ' ';
                }
                return os;
            }

            std::istream& read(std::istream& is) {
                T datum;
                size_type i
                for (i = 0; i < capacity(); ++i) {
                    is >> datum;
                    if (is.eof()) break;
                    push_back(datum);
                }
                return is;
            }

        private:

            size_type size_;
            size_type capacity_;

            value_type* data_;

        };

}

// non-member function overloads

template<typename T, jtl::size_t N>
std::ostream& operator<<(std::ostream& os, const jtl::data_vector<T, N>& v) {
    return v.write(os);
}

template<typename T, jtl::size_t N>
std::istream& operator>>(std::istream& is, jtl::data_vector<T, N>& v) {
    return v.read(is);
}

template <class T, jtl::size_t N>
bool operator!= (const jtl::data_vector<T, N>& lhs, const jtl::data_vector<T, N>& rhs) {
    return !(lhs == rhs);
}

template <class T, jtl::size_t N>
bool operator<= (const jtl::data_vector<T, N>& lhs, const jtl::data_vector<T, N>& rhs) {
    return !(rhs < lhs);
}

template <class T, jtl::size_t N>
bool operator>  (const jtl::data_vector<T, N>& lhs, const jtl::data_vector<T, N>& rhs) {
    return rhs < lhs;
}

template <class T, jtl::size_t N>
bool operator>= (const jtl::data_vector<T, N>& lhs, const jtl::data_vector<T, N>& rhs) {
    return !(lhs < rhs);
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

#endif