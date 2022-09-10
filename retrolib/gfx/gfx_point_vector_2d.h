/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      31.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef GFX_POINT_VECTOR_2D_H
#define GFX_POINT_VECTOR_2D_H

#include <fstream>
#include <string>

#include "../dos/dos_error_messages.h"

#include "../memory/checksum.h"
#include "../memory/data_vector.h"
#include "../memory/memory_unions.h"
#include "../memory/size_t.h"


#include "gfx_point_2d.h"

namespace gfx {

        template<jtl::size_t N>
        class point_vector_2d {

            typedef data_vector<uint32_t, N> point_vector_t;

        public:

// member types

            typedef uint32_t point_type;
            typedef const point_type* const_pointer;
            typedef size_t size_type;

// construction

            // empty container constructor
            point_vector_2d() : points(new point_vector_t) {}

            // file data
            point_vector_2d(std::string file_path) : points(new point_vector_t) {
                std::ifstream is(file_path.c_str());
                if (!is.is_open()) {
                    std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';                    
                }
                else {
                    read(is);
                }              
            }

            // file data using a specific file format reader functor
            template<typename FileFormatReader>
            point_vector_2d(std::string file_path, FileFormatReader read) : points(new point_vector_t) {
                points->resize(read(file_path, points->data()));
            }

            // range constructor
            template<typename InputIterator>
            point_vector_2d(InputIterator first, const InputIterator last) :
                points(new point_vector_t(first, last))
            {}

            //copy constructor
            point_vector_2d(const point_vector_2d& other) :
                points(new point_vector_t(other))
            {}

            // destructor
            ~point_vector_2d() {
                delete points;
            }

// iterators

// capacity

            inline size_type size() const {
                return points->size();
            }

            inline size_type capacity() {
                return points->capacity();
            }

// element access

            inline const_pointer data() const {
                return points->data();
            }

// modifiers

            void add(size_type x, size_type y) {
                union_point_t p(x, y);
                points->push_back(p.dword);
            }

            void add(const size_type* data, size_t n) {
                size_t i = 0;
                while (i < n) {
                    union_point_t p(data[i++], data[i++]);
                    points->push_back(p.dword);
                }
            }

            inline void clear() {
                points->clear();
            }

// relational operators

// ordering operations

//manipulating operations

            void translate(size_type x, size_type y) {
                union_point_t point(x, y);
                for (point_vector_t::iterator it = points->begin(); it < points->end(); ++it) {
                        *it += point.dword;
                }
            }

// serialisation

            std::istream& read(std::istream& is) {
                clear();
                uint16_t x, y;
                for (size_type i = 0; i < capacity(); ++i) {
                    is >> x;
                    if (is.eof()) break;
                    is >> y;
                    if (is.eof()) break;
                    add(x, y);
                }
                return is;
            }

            std::ostream& write(std::ostream& os) const {
                for (size_t i = 0; i < points->size(); ++i) {
                    union_point_t point(points->operator[](i));
                    os << point.coord.x << ' ' << point.coord.y << ' ';
                }
                return os;
            }

        private:

                point_vector_t* points;

        };

}

// non-member function overloads

template<jtl::size_t N>
std::ostream& operator<<(std::ostream& os, const jtl::point_vector_2d<N>& v) {
    return v.write(os);
}

template<jtl::size_t N>
std::istream& operator>>(std::istream& is, jtl::point_vector_2d<N>& v) {
    return v.read(is);
}

#endif