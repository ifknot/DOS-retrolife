/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef VGA_VIDEO_MODE_H
#define VGA_VIDEO_MODE_H

#include <stdint.h>

#include "vga_constants.h"
#include "../../bios/bios_video_services.h"

namespace vga {

	inline void text_mode() {
		bios::set_video_mode(bios::TEXT_16_COLOUR_80x25);
	}

	inline void graphics_mode() {
		bios::vga::enable_CPU_access_to_video_RAM();
		bios::set_video_mode(bios::GRAPHICS_256_COLOUR_320X200);
	}

}

#endif