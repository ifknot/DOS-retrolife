/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      31.05.2022
 *  @copyright � Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef POINT_2D_H
#define POINT_2D_H

#include <stdint.h>

namespace jtl {

    struct point_t {

        int16_t y, x;  

    };


    union union_point_t {

        uint32_t dword;
        point_t coord;

        union_point_t() : dword(0) {}

        union_point_t(uint32_t dword) : dword(dword) {}

        union_point_t(int16_t x, int16_t y) {
            coord.x = x;
            coord.y = y;
        }

    };

}

#endif