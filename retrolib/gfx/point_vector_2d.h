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

#include "../dos/dos_error_messages.h"

#include "../file/checksum.h"

#include "../memory/data_vector.h"
#include "../memory/memory_unions.h"
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

                inline const_pointer data() const {
                    return points.data();
                }

// modifiers

                void add(size_type x, size_type y) {
                    union_point_t point(x, y);
                    points.push_back(point.dword);
                }

                inline void clear() {
                    points.clear();
                }

// relational operators

// ordering operations

//manipulating operations

                void translate(size_type x, size_type y) {
                    union_point_t point(x, y);
                    for (point_vector_t::iterator it = points.begin(); it < points.end(); ++it) {
                            *it += point.dword;
                    }
                }

// serialisation

        std::istream& read(std::istream& is) {
            return points.read(is);
        }

        std::ostream& write(std::ostream& os) const {
            for (size_t i = 0; i < points.size(); ++i) {
                union_point_t point(points[i]);
                os << point.p.x << ' ' << point.p.y << ' ';
            }
            return os;
        }

        void read(std::string file_path) {
            std::ifstream is(file_path.c_str());
            if (!is.is_open()) {
                std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';
            }
            point_vector_t::size_type size;
            is >> size;
            points.resize(size);
            for (size_t i = 0; i < points.size(); ++i) {
                union_point_t point;
                is >> point.p.x;
                is >> point.p.y;
                points[i] = point.dword;
            }
        }

        void write(std::string file_path) {
            std::ofstream os(file_path.c_str());
            if (!os.is_open()) {
                std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';
            }
            os << size() << ' ';
            write(os);
        }

        void read_binary(std::string file_path) {
            std::ifstream is(file_path.c_str());
            if (!is.is_open()) {
                std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';
            }
            union_dword_t header;
            is.read(reinterpret_cast<char*>(&header.word), sizeof(header.word));
            points.resize(header.word.hi);
            is.read(reinterpret_cast<char*>(points.data()), size() * sizeof(point_vector_t::value_type));
        }

        void write_binary(std::string file_path) {
            std::ofstream os(file_path.c_str());
            if (!os.is_open()) {
                std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';
            }
            uint16_t sum = checksum(points.data(), size());
            union_dword_t header(size(), sum);
            os.write(reinterpret_cast<const char*>(&header.dword), sizeof(header.dword));
            os.write(reinterpret_cast<const char*>(points.data()), size() * sizeof(point_vector_t::value_type));
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