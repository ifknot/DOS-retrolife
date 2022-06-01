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
			jtl::point_vector_2d<256> a, b;
			std::cout << std::hex;
			std::cout << a.size() << ' ' << a << '\n';
			a.add(100, 10);
			std::cout << a.size() << ' ' << a << '\n';

			a.write("resource/pvec.dat");

			b.read("resource/pvec.dat");
			std::cout << b.size() << ' ' << b << '\n';

		}
		std::cout << "success!\n";
	}

}

#endif