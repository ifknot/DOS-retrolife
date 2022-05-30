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

#include "array.h"
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
                typedef jtl::array<char, 12> chars_t;
                chars_t c = { 'a','b','c','d','e','f','g','h','i','j','k','l' };
                vec_t a(c.begin(), c.end());
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
            
            std::cout << "success!\n";
        }

}

#endif