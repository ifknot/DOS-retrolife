/**
 *
 *  @file      test_array.h
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      29.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_ARRAY_H
#define TEST_ARRAY_H

#include <cassert>
#include <iostream>
#include <fstream>

#include "array.h"

namespace test_array {

        void run() {
            std::cout << "test_array...\n";
            {
                std::cout << "iterators\n";
                typedef jtl::array<char, 12> chars_t;
                char c = 'a';
                chars_t a;
                for (chars_t::iterator it = a.begin(); it < a.end(); ++it) {
                    *it = c++;
                }
                c = 'a';
                for (chars_t::const_iterator it = a.begin(); it < a.end(); ++it) {
                    assert(*it == c++);
                }
            }
            {
                std::cout << "capacity\n";
                jtl::array<int, 4> numbers = { 3, 1, 4, 1 };
                jtl::array<int, 0> no_numbers;
                assert(numbers.size() == 4);
                assert(no_numbers.size() == 0);
                assert(numbers.size() == 4);
                assert(no_numbers.size() == 0);
                assert(!numbers.empty());
                assert(no_numbers.empty());
            }
            {
                std::cout << "modifiers\n";
                jtl::array<int, 100> a;
                for (int i = 0; i < 100; ++i) a[i] = i + 1;
                jtl::array<int, 100> b;
                b.clear();
                jtl::array<int, 100> c;
                c.fill(123);

                std::cout << "element access\n";
                for (int i = 0; i < 100; ++i) assert(a[i] == i + 1);
                assert(a.front() == 1);
                a.front() = 100;
                assert(a.front() == 100);
                assert(a.back() == 100);
                a.back() = 1;
                assert(a.back() == 1);
                assert(*a.data() == 100);
                // no compile *a.data() = 123;
                assert(*(a.data() + 50) == 51);

                for (int i = 0; i < 100; ++i) assert(b[i] == 0);
                assert(b.front() == 0);
                b.front() = 100;
                assert(b.front() == 100);
                assert(b.back() == 0);
                b.back() = 1;
                assert(b.back() == 1);
                assert(*b.data() == 100);
                assert(*(b.data() + 50) == 0);

                for (int i = 0; i < 100; ++i) assert(c[i] == 123);
                assert(c.front() == 123);
                assert(c.back() == 123);
                assert(*c.data() == 123);
                assert(*(c.data() + 50) == 123);

                std::cout << "relational\n";
                b.fill(123);
                assert(c == b);
                assert(a != b);
                b.fill(124);
                assert(c < b);
                assert(b > c);
                c = b;
                assert(c <= b);
                assert(b >= c);
            }
            {
                std::cout << "serialisation\n";
                jtl::array<uint32_t, 12> a = { 1,2,3,4,5,6,7,8,9,10,11,12 };
                jtl::array<uint32_t, 12> b;
                b.clear();
                std::cout << a << '\n';
                std::cout << b << '\n';
                std::ofstream os("resource/array.dat");
                os << a;
                os.close();
                std::ifstream is("resource/array.dat");
                is >> b;
                assert(a == b);
            }
            std::cout << "success!\n";
        }

}

#endif