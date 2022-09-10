/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_GLYPH_H
#define TEST_GLYPH_H

#include <cassert>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include "gfx_glyph.h"

namespace test_glyph {

	void run() {

		// 32x16 pixel glyph uses 64 bytes of data
		typedef gfx::glyph<32, 16> glyph32x16_t;

		std::cout << "test_glyph... \n";
		{			
			std::cout << "constructors\n";
			// zero size
			glyph32x16_t a;
			assert(a.size() == 0);
			assert(a.capacity() == 64);
			// fill
			glyph32x16_t b(0xAA);
			assert(b.size() == 64);
			assert(b.capacity() == 64);
			for (int i = 0; i < 64; ++i) {
				assert(b.bytes()[i] == 0xAA);
			}
			// range 
			uint8_t v[64] = {
				0xAA, 0xAA, 0xAA, 0xAA,
				0x55, 0x55, 0x55, 0x55,
				0xAA, 0xAA, 0xAA, 0xAA,
				0x55, 0x55, 0x55, 0x55,
				0xAA, 0xAA, 0xAA, 0xAA,
				0x55, 0x55, 0x55, 0x55,
				0xAA, 0xAA, 0xAA, 0xAA,
				0x55, 0x55, 0x55, 0x55,
				0xAA, 0xAA, 0xAA, 0xAA,
				0x55, 0x55, 0x55, 0x55,
				0xAA, 0xAA, 0xAA, 0xAA,
				0x55, 0x55, 0x55, 0x55,
				0xAA, 0xAA, 0xAA, 0xAA,
				0x55, 0x55, 0x55, 0x55,
				0xAA, 0xAA, 0xAA, 0xAA,
				0x55, 0x55, 0x55, 0x55
			};
			glyph32x16_t c(v, v + 64);
			assert(c.size() == 64);
			assert(c.capacity() == 64);
			for (int i = 0; i < 64; ++i) {
				std::cout << c.bytes()[i] << ' ';
			}
			//copy
			glyph32x16_t d(b);
			assert(d.size() == 64);
			assert(d.capacity() == 64);
			for (int i = 0; i < 64; ++i) {
				assert(d.bytes()[i] == 0xAA);
			}
		}
		//
		std::cout << "success!\n";
	}

}

#endif