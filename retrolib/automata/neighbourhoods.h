/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef NEIGHBOURHOODS_H
#define NEIGHBOURHOODS_H

#include <stdint.h>

namespace jtl {

	namespace automata {

		namespace neighbourhood {

			const uint16_t moore_size = 8;

			const uint32_t moore[moore_size] = {
				0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001, 0x0000FFFF,
				0x00000001, 0x0001FFFF, 0x00010000, 0x00010001
			};

			const uint16_t von_neumann_size = 4;

			const uint32_t von_neumann[von_neumann_size] = {
				0xFFFF0000, 0x0000FFFF,
				0x00000001, 0x00010000
			};

		}

	}

}

#endif