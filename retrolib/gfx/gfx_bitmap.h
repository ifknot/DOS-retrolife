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

#define BMP_WIDTH		0
#define BMP_HEIGHT		2
#define BMP_DEPTH		4
#define BMP_MODE		5
#define BMP_SIZE		6
#define BMP_DATA		8

namespace gfx {

	struct bitmap {
		
		bitmap(uint16_t width, uint16_t height, uint8_t depth, uint8_t mode, uint8_t* data) :
			width(width),
			height(height),
			depth(depth),
			mode(mode),
			size(width * height * (depth / 8)),
			data(data)
		{}

		uint16_t width;				// bitmap width in pixels
		uint16_t height;			// bitmap height in pixels
		uint8_t depth;				// bits per pixel, ie colour depth of the image, typical values are 1, 4, 8, 16, 24 and 32
		uint8_t mode;				// mode - BIOS screen modes (bios::video_mode_t) + HGA graphics modes HGA0, HGA1, HGA2 (for herc, herc+, herc incolor)
		uint16_t size;				// size in bytes of the raw bitmap data
		uint8_t* data;				// pointer to size bytes of raw pixel data

	};

}

#endif