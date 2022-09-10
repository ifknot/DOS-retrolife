/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_GRAPHICS_READ_PIXEL_H
#define HGA_GRAPHICS_READ_PIXEL_H

#include "hga_graphics_constants.h"

namespace hga {

	namespace graphics {

		namespace screen_bound {

			inline colour_t read_pixel(size_type x, size_type y, uint8_t buffer = 0) {
				return 0;
			}

		}

		namespace toroid_bound {

			inline colour_t read_pixel(size_type x, size_type y, uint8_t buffer = 0) {
				return 0;
			}

		}

	}

}

#endif