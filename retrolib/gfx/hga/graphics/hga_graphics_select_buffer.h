/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_GRAPHICS_SELECT_BUFFER_H
#define HGA_GRAPHICS_SELECT_BUFFER_H

#include <stdint.h>

#include "hga_graphics_environment.h"

namespace hga {

    namespace graphics {

        inline void select_buffer(uint8_t buffer) {
            active_buffer = buffer;
            __asm {
                .8086
    #ifdef STACKING
                push dx
                push ax
    #endif
                mov     dx, HGA_CONTROL_REGISTER
                test    buffer, 1
                jnz     L0
                mov     al, 00001010b; screen on graphics mode page 1
                out     dx, al
                jmp     END
           L0 : mov     al, 10001010b; screen on graphics mode page 2
                out     dx, al

                END :

    #ifdef STACKING
                pop     ax
                pop     dx
    #endif
            }
        }

    }

}

#endif