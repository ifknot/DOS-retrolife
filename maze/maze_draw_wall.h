/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      3.09.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MAZE_DRAW_WALL_H
#define MAZE_DRAW_WALL_H

#include "../retrolib/gfx/mda/mode7/mda_mode7_draw_vertical_line.h"
#include "../retrolib/gfx/mda/mode7/mda_mode7_draw_vertical_capped_line.h"

namespace game {

	void draw_wall_left(mda::size_type x, mda::size_type y, uint8_t offset) {
		const uint8_t wall_dimensions[21] = { // height, width, capped
			24, 1, 1,
			23, 8, 0,  
			15, 6, 0,
			 9, 4, 0,
			 5, 3, 0, 
			 1, 2, 1,
			 1, 1, 0	
		};
		offset = offset * 3;
		uint8_t h = wall_dimensions[offset];
		uint8_t w = wall_dimensions[offset + 1];
		uint8_t c = wall_dimensions[offset + 2];
		for (int i = 0; i < w; ++i) {
			if (c) {
				mda::mode7::screen_bound::draw_vertical_capped_line(x, y - 1, x, y + h + 1);
			}
			else {
				mda::mode7::screen_bound::draw_vertical_line(x, y, x, y + h);
				h -= 2;
				y++;
			}
			c ^= 1; // toggle the endcap flag
			x++;
			
			
		}
		
	}
	/*
	void draw_wall_right(mda::size_type x, mda::size_type y, uint8_t offset) {

	}
	*/
}

#endif