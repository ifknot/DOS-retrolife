/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      4.09.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MAZE_DRAW_TURN_H
#define MAZE_DRAW_TURN_H

#include "../retrolib/gfx/mda/mode7/mda_mode7_draw_vertical_line.h"

namespace game {

	void draw_turn_left(mda::size_type x, mda::size_type y, uint8_t offset) {
		const uint8_t wall_dimensions[21] = { // height, width
			24, 1,
			23, 8, 
			15, 6,
			 9, 4,
			 5, 3,
			 1, 2,
			 1, 1
		};
	}

}

#endif