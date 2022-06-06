/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef NEIGHBOURHOODS_H
#define NEIGHBOURHOODS_H

#include "../memory/array.h"
#include "../memory/size_t.h"

#include "../gfx/point_2d.h"

namespace jtl {

	const int16_t moore_neighbours[16] = {
		-1, -1,
		 0, -1,
		 1, -1,
		-1,  0,
		 1,  0,
		-1,  1,
		 0,  1,
		 1,  1
	};

	const int16_t von_neumann_neighbours[8] = {
		 0, -1,
		-1,  0,
		 1,  0,
		 0,  1
	};

}

#endif