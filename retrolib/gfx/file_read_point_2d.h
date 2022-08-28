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
			std::ifstream fis(file_path.c_str());
			if (!fis.is_open()) {
				std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';
				return 0;
			}
			int i = 0;
			gfx::union_point_t point;
			while (true) {
				fis >> point.coord.x;
				if (fis.eof()) break;
				fis >> point.coord.y;
				if (fis.eof()) break;
				data[i++] = point.dword;
			}
			return i;
		}

	};

}

#endif