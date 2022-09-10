/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      5.09.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef GFX_BITMAP_H
#define GFX_BITMAP_H

#include <stdint.h>

namespace gfx {

	struct bitmap {

		uint16_t size;			// size in bytes of the raw bitmap data
		uint16_t width;			// bitmap width in pixels
		uint16_t height;		// bitmap height in pixels
		uint8_t depth;			// bits per pixel, ie color depth of the image, typical values are 1, 4, 8, 16, 24 and 32
		uint8_t mode;			// DOS screen mode - 

		uint8_t* data;			// pointer to size bytes of raw pixel data

	};

}

#endif