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
#include <stdio.h>

#include "../gfx/hga/hga.h"
#include "../gfx/hga/hga_plot_point.h"

#include "point_vector_2d.h"

namespace test_point_vector_2d {

	void run() {
		std::cout << "test_point_vector_2d... \n";
		{
			jtl::point_vector_2d<256> a, b;
			std::cout << std::hex;
			std::cout << a.size() << ' ' << a << '\n';
			a.add(0, 0);
			a.add(1, 1);
			a.add(2, 1);
			a.add(0, 2);
			a.add(1, 2);
			a.translate(100, 100);
			std::cout << a.size() << ' ' << a << '\n';

			a.write("resource/pvec.dat");

			b.read("resource/pvec.dat");
			std::cout << b.size() << ' ' << b << '\n';
			std::cout << "\nswitch to gfx mode Press <ENTER>";
			
			std::getchar();
			hga::graphics_mode();
			hga::cls();

			hga::screen_bound::plot_multi_point(b.data(), b.size());

			std::getchar();
			hga::text_mode();

		}
		std::cout << "success!\n";
	}

}

#endif