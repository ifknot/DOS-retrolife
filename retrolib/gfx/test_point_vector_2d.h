/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      31.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_POINT_VECTOR_2D_H
#define TEST_POINT_VECTOR_2D_H

#include <cassert>
#include <iostream>
#include <fstream>

#include "point_vector_2d.h"

namespace test_point_vector_2d {

	void run() {
		std::cout << "test_point_vector_2d... \n";
		{
			jtl::point_vector_2d<256> a;
			std::cout << std::hex;
			std::cout << a.size() << ' ' << a << '\n';
			a.add(0xDEAD, 0xBEEF);
			std::cout << a.size() << ' ' << a << '\n';

			
		}
		std::cout << "success!\n";
	}

}

#endif