/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      29.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_DATA_VECTOR_H
#define TEST_DATA_VECTOR_H

#include <cassert>
#include <iostream>
#include <fstream>

#include "data_vector.h"

typedef jtl::data_vector<int> vec_t;

void print(vec_t& v) {
    std::cout << v.size() << ' ' << v.capacity() << ' ' << v.max_size() << '\n';
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

namespace test_data_vector {

        void run() {
            std::cout << "test_data_vector... \n";
            {
                std::cout << "iterators\n";
                char c[12] = { 'a','b','c','d','e','f','g','h','i','j','k','l' };
                vec_t a(c, c + 12);// , true);
                char ch = 'a';
                for (vec_t::const_iterator it = a.begin(); it < a.end(); ++it) {
                    assert(*it == ch++);
                }
                vec_t b(a);
                ch = 'a';
                for (vec_t::const_iterator it = a.begin(); it < a.end(); ++it) {
                    assert(*it == ch++);
                }
            }
            {
                std::cout << "capacity\n";
                vec_t a(4);
                vec_t b;
                assert(a.size() == 4);
                assert(b.size() == 0);
                assert(a.size() == 4);
                assert(b.size() == 0);
                assert(!a.empty());
                assert(b.empty());
                a.clear();
                assert(a.empty());
                assert(a.capacity() == 256);
                std::cout << a.max_size() << ' ' << sizeof(int) << '\n';
                assert(vec_t::max_size() == 0xFFFF / sizeof(int));
            }
            {
                std::cout << "element access\n";
                vec_t v;
                int sum = 0;
                v.push_back(10);
                v.push_back(10);
                v.push_back(30);
                v[1] += 10;
                v = v * v;
                v *= 2;
                while (!v.empty()) {
                    sum += v.back();
                    v.pop_back();
                }
                assert(sum == 2800);
            }
            {
                std::cout << "modifiers\n";
            }
            {
                std::cout << "realtional\n";
                vec_t a(100);
                jtl::data_vector<char> chars(100, 'a');
                vec_t b(100, 123, true);
                b += 123;
                vec_t c(b);
                assert(c == b);
                assert(a != b);
                b += 1;
                assert(c < b);
                assert(b > c);
                c = b;
                assert(c <= b);
                assert(b >= c);
            }
            {
                std::cout << "serialisation\n";
                jtl::data_vector<char> a(100, 'a');
                jtl::data_vector<char> b(100);
                std::cout << a << '\n';
                std::cout << b << '\n';
                for (int i = 0; i < 50; ++i) a.pop_back();
                std::cout << a << '\n';
                for (int i = 0; i < 50; ++i) a.push_back('A' + i);
                std::cout << a << '\n';
                std::ofstream os("resource/data_vec.dat");
                os << a;
                os.close();
                std::ifstream is("resource/data_vec.dat");
                is >> b;
                assert(a == b);

            }
            std::cout << "success!\n";
        }

}

#endif