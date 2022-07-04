/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      4.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef FILE_READ_POINT_LIST_H
#define FILE_READ_POINT_LIST_H

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>

#include "../dos/dos_error_messages.h"

namespace dosgol {

	struct read_point_list {

		int operator()(std::string file_path, uint32_t* data) {
			std::ifstream is(file_path.c_str());
			if (!is.is_open()) {
				std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';
				return 0;
			}
			while (!is.eof()) {

			}
		}

	};

}

#endif