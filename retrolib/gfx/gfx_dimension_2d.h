/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      27.08.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef GFX_DIMENSION_2D_H
#define GFX_DIMENSION_2D_H

#include <stdint.h>

namespace gfx {

    struct dimension_t {

        int16_t height, width;

    };

    union union_dimension_t {

        uint32_t dword;
        dimension_t dim;

        union_dimension_t() : dword(0) {}

        union_dimension_t(uint32_t hw) {
            dim.height = static_cast<int16_t>(hw);
            dim.width = static_cast<int16_t>(hw >> 16);
        }

        union_dimension_t(int16_t width, int16_t height) {
            dim.height = height;
            dim.width = width;
        }

    };

}

#endif