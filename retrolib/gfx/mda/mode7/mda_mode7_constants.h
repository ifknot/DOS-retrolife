/**
 *
 *  @brief     semigraphics for MDA
 *  @details   use text mode video hardware code page 437 to emulate raster graphics
 *  @url https://en.wikipedia.org/wiki/Semigraphics
 *  @author    Jeremy Thornton
 *  @date      20.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MDA_MODE7_CONSTANTS_H
#define MDA_MODE7_CONSTANTS_H

#include "../mda_constants.h"

#define SCREEN_X_MIN 0
#define SCREEN_X_MAX 80
#define SCREEN_Y_MIN 0
#define SCREEN_Y_MAX 25

namespace mda {

	namespace mode7 {

		namespace colour {

			enum inks {
				black = 0x20,
				light_gray = 0xB0,
				gray,
				dark_gray,
				white = 0xDB
			};

		}

		namespace attribute {

			enum attributes {
				invisible,
				normal,
				underline,
				bright,
				bright_underline,
				reverse,
				invisible_reverse
			};

		}

	}

}

#endif