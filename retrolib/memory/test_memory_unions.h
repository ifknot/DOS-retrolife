/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      1.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_MEMORY_UNIONS_H
#define TEST_MEMORY_UNIONS_H

#include <cassert>
#include <iostream>
#include <fstream>
#include <stdint.h>

#include "memory_unions.h"

namespace test_memory_unions {

	void run() {

		std::cout << "test_memory_unions... \n";
		{
			std::cout << std::hex;
			jtl::union_word_t w(0xbeef);
			std::cout << w.word << ' ' << (int)w.byte.hi << ' ' << (int)w.byte.lo << ' '
				<< (int)w.bytes[0] << ' ' << (int)w.bytes[1] << '\n';

		}
		{
			std::cout << std::hex;
			jtl::union_dword_t w(0xdeadbeef);
			std::cout 
				<< w.dword << ' ' 
				<< w.word.hi << ' ' << w.word.lo << ' '
				<< w.bytes[0] << ' ' << w.bytes[1] << ' '
				<< w.bytes[2] << ' ' << w.bytes[3] << '\n';
		}
		std::cout << "success!\n";

	}

}

#endif