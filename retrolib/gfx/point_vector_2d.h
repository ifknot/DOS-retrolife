/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      31.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef POINT_VECTOR_2D_H
#define POINT_VECTOR_2D_H

#include <string>

#include "../memory/data_vector.h"

#define MAX_POINTS 8192 // 32K of 32bit points

namespace jtl{

	template<typename T>
	class point_vector_2d {

		typedef data_vector<T, MAX_POINTS> point_vector_t;

	public:

		typedef T point_type;
		typedef const point_type* const_pointer;

		void add(uint16_t x, uint16_t y) {
			point_type p = y;
			y <= 16;
			p |= x;
		}

		inline const_pointer data() {
			return points.data();
		}

	private:

		point_vector_t points;

	};

}

#endif