/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      31.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef POINT_VECTOR_2D_H
#define POINT_VECTOR_2D_H

#include <fstream>
#include <string>

#include "..\dos\dos_error_messages.h"

#include "../memory/data_vector.h"
#include "../memory/size_t.h"

#include "point_2d.h"

namespace jtl{

        template<size_t N>
        class point_vector_2d {

                typedef data_vector<uint32_t, N> point_vector_t;

        public:

// member types

                typedef uint32_t point_type;
                typedef const point_type* const_pointer;
                typedef size_t size_type;

// construction

// iterators

// capacity

                inline size_type size() const {
                        return points.size();
                }

// element access

                inline const_pointer data() {
                        return points.data();
                }

// modifiers

                void add(size_type x, size_type y) {
                        union_point_t point;
                        point.p.x = x;
                        point.p.y = y;
                        points.push_back(point.dword);
                }

                inline void clear() {
                        points.clear();
                }

// relational operators

// ordering operations

//manipulating operations

                void translate(size_type x, size_type y) {
                        union_point_t p;
                        p.p.x = x;
                        p.p.y = y;
                        for (point_vector_t::iterator it = points.begin(); it < points.end(); ++it) {
                                *it += p.dword;
                        }
                }

// serialisation

        std::istream& read(std::istream& is) {
            return points.read(is);
        }

        std::ostream& write(std::ostream& os) const {
            return points.write(os);
        }

        void save(std::string file_path) {
            std::ofstream os(file_path.c_str(), std::ofstream::binary);
            if (!f->is_open()) {
                std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';
            }
        }

        void load(std::string file_path) {

        }

        private:

                point_vector_t points;

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