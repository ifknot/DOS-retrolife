/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      4.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef FILE_READ_POINT_2D_H
#define FILE_READ_POINT_2D_H

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>

#include "../dos/dos_error_messages.h"

#include "point_2d.h"

namespace jtl {

	struct file_read_point_2d {

		int operator()(std::string file_path, uint32_t* data) {
			std::ifstream is(file_path.c_str());
			if (!is.is_open()) {
				std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';
				return 0;
			}
			int i = 0;
			union_point_t point;
			while (!is.eof()) {
				is >> point.coord.x;
				if (is.eof()) {
					std::cerr << dos::error::messages[dos::error::INVALID_FORMAT] << file_path.c_str() << '\n';
					break;
				}
				is >> point.coord.y;
				data[i++] = point.dword;
			}
			return i;
		}

	};

}

#endif