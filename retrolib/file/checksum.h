/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      31.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef CHECKSUM_H
#define CHECKSUM_H

#include "../memory/size_t.h"

namespace jtl {

	template<typename T, typename U>
	U checksum(T* data, U n) {
		U sum = 0;
		for (U i = 0; i < n; ++i) {
			sum += static_cast<U>(*data++);
		}
		return sum;
	}

}


#endif