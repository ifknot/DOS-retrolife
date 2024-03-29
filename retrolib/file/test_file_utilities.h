/**
 *
 *  @file      test_file_utilities.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.03.2022
 *  @copyright � Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_FILE_UTILITIES_H
#define TEST_FILE_UTILITIES_H

#include <cassert>
#include <iostream>

#include "file_extension.h"

namespace test_file_utilities {

	void run() {
		std::cout << "test_file_utilities... ";
		//test filesystem::extension
		{
			assert(jtp::filesystem::extension("test.dat") == "dat");
		}
		std::cout << "success!\n";
	}

}

#endif