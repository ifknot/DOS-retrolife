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
		
		uint16_t width;			// bitmap width in pixels
		uint16_t height;		// bitmap height in pixels
		uint8_t offset;			// offset in bytes to raw pixel data
		uint16_t size;			// size in bytes of the raw bitmap data
		uint8_t depth;			// bits per pixel, ie color depth of the image, typical values are 1, 4, 8, 16, 24 and 32
		uint8_t mode;			// mode - BIOS screen modes (bios::video_mode_t) + HGA graphics modes HGA0, HGA1, HGA2 (for herc, herc+, herc incolor)

		uint8_t* data;			// pointer to size bytes of raw pixel data

	};

}

#endif