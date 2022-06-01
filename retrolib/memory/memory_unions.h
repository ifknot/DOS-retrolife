/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      1.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MEMORY_UNIONS_H
#define MEMORY_UNIONS_H

#include <stdint.h>

#define LITTLE_ENDIAN

namespace jtl {

#ifdef LITTLE_ENDIAN

	struct word_t {

		int8_t hi, lo; 

	};

#endif

	union union_word_t {

		uint16_t word;
		word_t byte;
		int8_t bytes[2];

		union_word_t() : word(0) {}

		union_word_t(int16_t word) : word(word) {}

		union_word_t(int8_t hi, int8_t lo) {
			byte.hi = hi;
			byte.lo = lo;
		}

	};

#ifdef LITTLE_ENDIAN

	struct dword_t {

		int16_t hi, lo;

	};

#endif

	union union_dword_t {

		uint32_t dword;
		dword_t word;
		int8_t bytes[4];

		union_dword_t() : dword(0) {}

		union_dword_t(int32_t dword) : dword(dword) {}

		union_dword_t(int16_t hi, int16_t lo) {
			word.hi = hi;
			word.lo = lo;
		}

	};

}

#endif