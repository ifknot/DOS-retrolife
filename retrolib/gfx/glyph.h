/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef GLYPH_H
#define GLYPH_H

#include "../memory/data_vector.h"
#include "../memory/size_t.h"

namespace jtl {

        template<size_t W, size_t H>
        class glyph {

                typedef data_vector<uint8_t, (W / 8) * H> byte_vector_t;

        public:

// member types

        typedef size_t size_type;
        typedef byte_vector_t::value_type value_type;
        typedef const value_type* const_pointer;

// construction

        // empty container constructor
        glyph() : bytes_(new byte_vector_t) {}

        // fill constructor
        glyph(value_type val) : bytes_(new byte_vector_t(byte_vector_t::capacity(), val)) {}

        // range constructor
        template<typename InputIterator>
        glyph(InputIterator first, const InputIterator last) : bytes_(new byte_vector_t(first, last)) {}

        //copy constructor
        glyph(const glyph& other) : bytes_(new byte_vector_t(*other.bytes_)) {}

        // file data

        // destructor
        ~glyph() {
            delete bytes_;
        }

// iterators

// capacity

        inline size_type width() {
            return W;
        }

        inline size_type height() {
            return H;
        }


        inline size_type size() const {
            return bytes_->size();
        }

        inline size_type capacity() const {
            return bytes_->capacity();
        }

// element access

        inline const_pointer bytes() const {
            return bytes_->data();
        }

// modifiers

        byte_vector_t& operator=(const byte_vector_t& other) {
            assert(size() == other.size());
            if (this != &other) {
                for (size_type i = 0; i < size_; ++i) data_[i] = other.data_[i];
            }
            return *this;
        }

// relational operators

// ordering operations

//manipulating operations

// serialisation

        private:

        byte_vector_t* bytes_;

        };

}

#endif