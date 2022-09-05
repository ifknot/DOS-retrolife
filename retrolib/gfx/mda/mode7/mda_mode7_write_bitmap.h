/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      5.09.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MDA_MODE7_WRITE_BITMAP_H
#define MDA_MODE7_WRITE_BITMAP_H

#include "mda_mode7_constants.h"
#include "../../../dos/dos_address_t.h"

namespace mda {

	namespace mode7 {

        namespace screen_bound {

            void write_bitmap(size_type x, size_type y, uint8_t* data) {
                dos::address_t addr((uint32_t)data);
                __asm {
                    .8086

                }
            }

        }

        namespace torus_bound {

        }

	}

}

#endif