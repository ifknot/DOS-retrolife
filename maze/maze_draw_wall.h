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

	static const uint8_t wall_dimensions[21] = {
		// width, height, capped
			1,		24,		1,	// distance 0
			8,		23,		0,	// distance 1	
			6,		15,		0,	// distance 2
			4,		 9,		0,	// distance 3
			3,		 5,		0,	// distance 4 
			2,		 1,		1,	// distance 5
			1,		 1,		0	// distance 6	
	};

	void draw_wall_left(mda::size_type x, mda::size_type y, uint8_t distance) {	
		uint8_t offset = distance * 3; // convert distance to offset into wall dimension array
		uint8_t w = wall_dimensions[offset];
		uint8_t h = wall_dimensions[offset + 1];
		uint8_t capped = wall_dimensions[offset + 2];
		for (int i = 0; i < w; ++i) { // draw width number of vertical line planks 
			if (capped) {
				mda::mode7::screen_bound::draw_vertical_capped_line(
					x, 
					y - 1,		// lengthen the start point to fit top cap
					x, 
					y + h + 1	// add the height of the plank and lengthen the end point to fit base cap
				);
			}
			else {
				mda::mode7::screen_bound::draw_vertical_line(
					x, 
					y, 
					x, 
					y + h		// add the height of the plank
				);
				h -= 2;			// shrink the wall height towards the vanishing point
				y++;			// start the next plank lower
			}
			capped ^= 1;		// toggle the endcap flag
			x++;				// next plank to the right 	
		}
	}
	
	void draw_wall_right(mda::size_type x, mda::size_type y, uint8_t distance) {
		uint8_t offset = distance * 3; // convert to offset into wall dimension array
		uint8_t h = wall_dimensions[offset];
		uint8_t w = wall_dimensions[offset + 1];
		uint8_t capped = wall_dimensions[offset + 2];
		for (int i = 0; i < w; ++i) { // draw width number of vertical line planks 
			if (capped) {
				mda::mode7::screen_bound::draw_vertical_capped_line(
					x, 
					y - 1,		// lengthen the start point to fit top cap
					x, 
					y + h + 1	// add the height of the plank and lengthen the end point to fit base cap
				);
			}
			else {
				mda::mode7::screen_bound::draw_vertical_line(
					x, 
					y, 
					x, 
					y + h		// add the height of the plank
				);
				h -= 2;			// shrink the wall height towards the vanishing point
				y++;			// start the next plank lower
			}
			capped ^= 1;		// toggle the endcap flag
			x--;				// next plank to the left	
		}
	}
	
}

#endif