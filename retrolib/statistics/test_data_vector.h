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



namespace test_data_vector {

	void run() {

		std::cout << "test_data_vector... \n";
		{
			typedef jtl::data_vector<uint32_t,12> point_vector_t;
			jtl::array<uint32_t, 12> dots = { 1,2,3,4,5,6,7,8,9,10,11,12 };
			point_vector_t points(dots);
			std::cout << points << '\n';
			assert(points.size() == 12);
			points.clear();
			std::cout << points << '\n';

			jtl::data_vector<float, 4> a, b;
			a.clear();
			b = a;
			std::cout << a << '\n';
			assert(a == 0);
			assert(a == b);
			std::ofstream odata("resource/dataf.dat");
			odata << a;
			std::ifstream idata("resource/testf.dat");
			idata >> a;
			b = a;
			std::cout << a << '\n';
			std::cout << b << '\n';
			a += 10.0;
			std::cout << a << '\n';
			a += a;
			std::cout << a << '\n';
			jtl::data_vector<float, 4> c = a + b;
			std::cout << c << '\n';
		}
		std::cout << "success!\n";
	}

}

#endif