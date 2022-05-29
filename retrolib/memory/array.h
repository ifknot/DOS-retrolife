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
#include "null_ptr_t.h"
#include "swap.h"

namespace jtl {

    template<typename T, size_t N>
    class array {

    public:

        typedef T value_type;
        typedef size_t size_type;
        //typedef ptrdiff_t     difference_type
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;

        array& operator=(const array& other) {
            assert(size() == other.size());
            if (this != &other) {
                for (size_type i = 0; i < size(); ++i) data_[i] = other.data_[i];
            }
            return *this;
        }

        inline reference operator[](size_type pos) {
            return data_[pos];
        }

        inline const_reference operator[](size_type pos) const {
            return data_[pos];
        }

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

        inline size_type size() const {
            return N;
        }

        inline bool empty() const {
            return N == 0;
        }

        void clear() {
            for (size_type i = 0; i < size(); ++i) data_[i] = 0;
        }

        void fill(const value_type& value) {
            for (size_type i = 0; i < size(); ++i) data_[i] = value;
        }

        inline void swap(array& other) {
            array<T,N> temp = *this;
            *this = other;
            other = temp;
        }

        std::ostream& write(std::ostream& os) const {
            for (size_type i = 0; i < size(); ++i) {
                    os << data_[i] << ' ';
            }
                return os;
        }

        std::istream& read(std::istream& is) {
            T datum;
            for (size_type i = 0; i < size(); ++i) {                           
                is >> datum;
                if (is.eof()) break;
                data_[i] = datum;
            }
            return is;
        }

    protected:

        value_type data_[N];

    };

    template<typename T>
    struct array<T, 0> {

        typedef T value_type;
        typedef size_t size_type;
        //typedef ptrdiff_t     difference_type
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;

        inline size_type size() const {
            return 0;
        }

        inline bool empty() const {
            return true;
        }

        inline nullptr_t data() {
            return nullptr;
        }

    };

}

template<typename T, jtl::size_t N>
std::ostream& operator<<(std::ostream& os, const jtl::array<T, N>& a) {
        return a.write(os);
}

template<typename T, jtl::size_t N>
std::istream& operator>>(std::istream& is, jtl::array<T, N>& a) {
        return a.read(is);
}

#endif