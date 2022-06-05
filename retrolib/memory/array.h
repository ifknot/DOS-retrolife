/**
 *
 *  @file      array.h
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>
#include <ostream>
#include <istream>

#include "size_t.h"
#include "ptrdiff_t.h"
#include "null_ptr_t.h"

namespace jtl {

    template<typename T, size_t N>
    class array {

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

// construction

        // empty container constructor
        array() :
            data_(new T[N])
        {}

        // fill constructor
        explicit array(size_type n, const value_type& val = value_type(), bool f = true) :
            data_(new T[N])
        {
            assert(n <= N && f);
            while (n) {
                data_[--n] = val;
            }
        }

        // range constructor
        template<typename InputIterator>
        array(InputIterator first, const InputIterator last) :
            data_(new T[N])
        {
            assert(last - first <= N);
            size_type i = 0;
            while (first < last) {
                data_[i++] = *first++;
            }
        }

        //copy constructor
        array(const array& other) :
            data_(new T[N])
        {
            assert(other.size() <= N);
            for (size_type i = 0; i < other.size(); ++i) {
                data_[i] = other.data_[i];
            }
        }

        ~array() {
            delete[] data_;
        }

// iterators

        inline iterator begin() {
            return data_;
        }

        inline const_iterator begin() const {
            return &data_;
        }

        inline iterator end() {
            return data_ + N;
        }

        inline const_iterator end() const {
            return data_ + N;
        }

// capacity

        inline size_type size() const {
            return N;
        }

        inline size_type max_size() const {
            return N;
        }

        inline bool empty() const {
            return false;
        }

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
            return data_[N - 1];
        }

        inline const_reference back() const {
            return data_[N - 1];
        }

        inline const_pointer data() {
            return data_;
        }

// modifiers

        array& operator=(const array& other) {
            assert(size() == other.size());
            if (this != &other) {
                for (size_type i = 0; i < size(); ++i) data_[i] = other.data_[i];
            }
            return *this;
        }

        void zero() {
            for (size_type i = 0; i < size(); ++i) data_[i] = 0;
        }

        void fill(const value_type& value) {
            for (size_type i = 0; i < size(); ++i) data_[i] = value;
        }

        inline void swap(array& other) {
            array<T,N> temp_array = *this;
            *this = other;
            other = temp_array;
        }

// relational operators

        bool operator==(const array& rhs) const {
            assert(size() == rhs.size());
            for (size_type i = 0; i < size(); ++i) {
                if (data_[i] != rhs[i]) return false;
            }
            return true;
        }

        bool operator<(const array& rhs) const {
            assert(size() == rhs.size());
            for (size_type i = 0; i < size(); ++i) {
                if (data_[i] >= rhs[i]) return false;
            }
            return true;
        }

// serialisation

        std::ostream& write(std::ostream& os) const {
            for (size_type i = 0; i < N; ++i) {
                    os << data_[i] << ' ';
            }
            return os;
        }

        std::istream& read(std::istream& is) {
            T datum;
            for (size_type i = 0; i < N; ++i) {
                is >> datum;
                if (is.eof()) break;
                data_[i] = datum;
            }
            return is;
        }

    private:

        value_type* data_;

    };

    template<typename T>
    struct array<T, 0> {

        typedef size_t size_type;

// capacity

        inline size_type size() const {
            return 0;
        }

        inline size_type max_size() const {
            return 0;
        }

        inline bool empty() const {
            return true;
        }

    };

}

// non-member function overloads

template<typename T, jtl::size_t N>
std::ostream& operator<<(std::ostream& os, const jtl::array<T, N>& a) {
        return a.write(os);
}

template<typename T, jtl::size_t N>
std::istream& operator>>(std::istream& is, jtl::array<T, N>& a) {
    return a.read(is);
}

template <class T, jtl::size_t N>
bool operator!= (const jtl::array<T, N>& lhs, const jtl::array<T, N>& rhs) {
    return !(lhs == rhs);
}

template <class T, jtl::size_t N>
bool operator<= (const jtl::array<T, N>& lhs, const jtl::array<T, N>& rhs) {
    return !(rhs < lhs);
}

template <class T, jtl::size_t N>
bool operator>  (const jtl::array<T, N>& lhs, const jtl::array<T, N>& rhs) {
    return rhs < lhs;
}

template <class T, jtl::size_t N>
bool operator>= (const jtl::array<T, N>& lhs, const jtl::array<T, N>& rhs) {
    return !(lhs < rhs);
}

#endif