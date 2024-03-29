/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright � Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_GRAPHICS_SWAP_BUFFERS_H
#define HGA_GRAPHICS_SWAP_BUFFERS_H

#include <stdint.h>

#include "hga_graphics_environment.h"

namespace hga {

    namespace graphics {

        inline void swap_buffers() {
            __asm {
                .8086
    #ifdef STACKING
                push dx
                push ax
    #endif
                xor     active_buffer, 1            ; flip to other page  using xor 0 -> 1 so 1 -> 0
                mov     dx, HGA_CONTROL_REGISTER
                test    active_buffer, 1
                jnz     L0
                mov     al, 00001010b               ; screen on
                out     dx, al
                jmp     END
           L0:  mov     al, 10001010b               ; screen on
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