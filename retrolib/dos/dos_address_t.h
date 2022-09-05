/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      5.09.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef DOS_ADDRESS_T
#define DOS_ADDRESS_T

#include <stdint.h>
#include <iostream>
#include <iomanip>

namespace dos {

	struct segoff_t {

		uint16_t offset, segment;

	};

	union address_t {

		uint32_t address;
		segoff_t memory;
		uint16_t words[2];
		uint8_t bytes[4];

		address_t() : address(0) {}

		address_t(uint32_t address) : address(address) {}

		address_t(uint16_t segment, uint16_t offset) {
			memory.segment = segment;
			memory.offset = offset;
		}

	};

}

#endif