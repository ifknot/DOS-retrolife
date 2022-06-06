/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      5.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_COUNT_NEIGHBOURS_H
#define TEST_COUNT_NEIGHBOURS_H

#include <cassert>
#include <iostream>

#include "neighbourhoods.h"

namespace test_count_neighbours {

	void run() {
		std::cout << "test_count_neighbours...\n";
		{
			jtl::union_point_t point(10, 10);
			std::cout << point.coord.x << ',' << point.coord.y << '\n';
			int16_t a = -1;
			point.coord.x += a;
			std::cout << point.coord.x << ',' << point.coord.y << '\n';

		}
		std::cout << "success!\n";
	}

}

#endif