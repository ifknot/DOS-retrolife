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

typedef jtl::data_vector<int, 256> vec_t;

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
                    
            }
            {
                std::cout << "capacity\n";
                vec_t a;
                print(a);
                

            }
            std::cout << "success!\n";
        }

}

#endif