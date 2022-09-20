/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      19.09.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MAZE_BITMAPS_H
#define MAZE_BITMAPS_H

#include <stdint.h>

#include "maze_items.h"
#include "../retrolib/gfx/mda/mode7/mda_mode7_constants.h"

using namespace mda::mode7::attribute;

namespace game {

	// distance 0 walls are a thin strip at the edge of the viewpoint
	// width, height, capped
	//	1,		25,		1,	
	uint8_t left_wall_0[50] = {
		LOWER_HALF_BLOCK, reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		UPPER_HALF_BLOCK, reverse,
	};

	uint8_t right_wall_0[50] = {
		LOWER_HALF_BLOCK, reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,
		UPPER_HALF_BLOCK, reverse,
	};
	
	// distance 1 walls are 8x23 = 184 words = 368 bytes
	// width, height, capped
	//	8,		23,		0,		
	uint8_t left_wall_1[368] = {
		FULL_BLOCK,reverse,LOWER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,LOWER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,LOWER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,LOWER_HALF_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,UPPER_HALF_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,UPPER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,UPPER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,
		FULL_BLOCK,reverse,UPPER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse
	};

	uint8_t right_wall_1[368] = {
		SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,LOWER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,
		SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,LOWER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		SPACE,reverse,SPACE,reverse,LOWER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		LOWER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		UPPER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		SPACE,reverse,SPACE,reverse,UPPER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,UPPER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,UPPER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,
	};

	// distance 2 walls are 6x15 =  90 words = 180 bytes
	// width, height, capped
	//	6,		15,		0,	
	uint8_t left_wall_2[180] = {
		FULL_BLOCK,reverse,LOWER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,LOWER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,LOWER_HALF_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,UPPER_HALF_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,UPPER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse,
		FULL_BLOCK,reverse,UPPER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse
	};

	uint8_t right_wall_2[180] = {
		SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,LOWER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,
		SPACE,reverse,SPACE,reverse,LOWER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		LOWER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		UPPER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		SPACE,reverse,SPACE,reverse,UPPER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		SPACE,reverse,SPACE,reverse,SPACE,reverse,SPACE,reverse,UPPER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,
	};

	// distance 3 walls are 4x9 =  36 words = 72 bytes
	// width, height, capped
	//	4,		 9,		0,	
	uint8_t left_wall_3[72] = {
		FULL_BLOCK,reverse,LOWER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,LOWER_HALF_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,UPPER_HALF_BLOCK,reverse,
		FULL_BLOCK,reverse,UPPER_HALF_BLOCK,reverse,SPACE,reverse,SPACE,reverse
	};

	uint8_t right_wall_3[72] = {
		SPACE,reverse,SPACE,reverse,LOWER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,
		LOWER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		UPPER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		SPACE,reverse,SPACE,reverse,UPPER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,
	};

	// distance 4 walls are 3x5 =  15words = 30 bytes
	// width, height, capped
	//	3,		 5,		0,	
	uint8_t left_wall_4[30] = {
		FULL_BLOCK,reverse,LOWER_HALF_BLOCK,reverse,SPACE,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,		
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,UPPER_HALF_BLOCK,reverse,SPACE,reverse
	};

	uint8_t right_wall_4[30] = {
		SPACE,reverse,LOWER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		FULL_BLOCK,reverse,FULL_BLOCK,reverse,FULL_BLOCK,reverse,
		SPACE,reverse,UPPER_HALF_BLOCK,reverse,FULL_BLOCK,reverse,
	};

}

#endif