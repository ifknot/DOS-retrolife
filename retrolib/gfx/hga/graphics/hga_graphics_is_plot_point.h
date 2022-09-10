/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_GRAPHICS_IS_PLOT_POINT_H
#define HGA_GRAPHICS_IS_PLOT_POINT_H

#include "hga_graphics_constants.h"

namespace hga {

    namespace graphics {

	    namespace screen_bound {

		    inline bool is_plot_point(uint32_t point, uint8_t buffer = 0) {
                uint8_t flag = 0;
                uint16_t y = static_cast<uint16_t>(point);
                point >>= 16;
                uint16_t x = static_cast<uint16_t>(point);
                __asm {
                    .8086
    #ifdef STACKING
                    push    ax
                    push    es
                    push    dx
                    push    bx
                    push    cx
                    push    di
    #endif
                    mov     ax, HGA_VIDEO_RAM_SEGMENT
                    test    buffer, 1               ; which buffer ?
                    jz      J0
                    add     ax, 800h                ; second buffer
            J0:     mov     es, ax
                    mov     ax, y                   ; load y into ax then perform screen clipping
                    cmp     ax, SCREEN_Y_MAX        ; compare ax with y maximum boundry
                    jge     END                     ; nothing to plot
                    mov     dx, ax                  ; copy y
    #ifdef ENABLE_MUL
                    shr     ax, 1                   ; calculate y / 4
                    shr     ax, 1                   ; 8086 limited to single step shifts
                    mov     cl, BYTES_PER_LINE
                    mul     cl                      ; calculate(y / 4) * 90
    #else
                    and     ax, 0FFFCh              ; mask out bank selection bits
                    mov     bx, ax                  ; copy y
                    shl     ax, 1
                    shl     ax, 1
                    mov     cx, ax                  ; copy y
                    shl     ax, 1                   ; 8086 shift left 2 times
                    shl     ax, 1                   ;
                    add     ax, cx                  ;
                    shr     bx, 1                   ; 8086 limited to single step shifts
                    mov     cx, bx                  ; copy y
                    shl     bx, 1                   ; 8086 shift left 2 times
                    shl     bx, 1                   ;
                    add     ax, cx                  ; + (y / 2)
                    add     ax, bx                  ; + (y * 4)
    #endif
                    and     dx, 00000011b           ; mask off only the bank select bits (0..4)
                    ror     dx, 1                   ; calculate 16-bit bank# * 2000h
                    ror     dx, 1                   ; 8086 limited to single step shifts
                    ror     dx, 1                   ; (y mod 4) * 2000h
                    mov     di, x                   ; load x into di and clip to screen bounds
                    cmp     di, SCREEN_X_MAX        ; compare di with x maximum boundry
                    jge     END                     ; nothing to plot
                    mov     cx, di                  ; copy of x in cx
                    shr     di, 1                   ; calculate column byte x / 8
                    shr     di, 1                   ; 8086 limited to single step shifts
                    shr     di, 1                   ; x / 8
                    add     di, ax                  ; + (y / 4) * 90
                    add     di, dx                  ; + (y mod 4) * 2000h
                    and     cx, 7h                  ; mask off 0111 lower bits i.e.mod 8 (thanks powers of 2)
                    mov     ah, 10000000b           ; load ah with single pixel at msb
                    ror     ah, cl                  ; shift single bit along by x mod 8
    #ifdef SYNCHRONISED

                    mov     dx, CGA_STATUS_REG      ; CGA status reg
            S0:     in      al, dx                  ; read status
                    test    al, 1000b               ; is bit 3 set ? (in a vertical retrace interval)
                    jnz     L0                      ; yes, keep waiting
            S1:     in      al, dx                  ; read status
                    test    al, 1000b               ; is bit 3 set ? (just started a vertical retrace interval)
                    jnz     L1                      ; no, keep waiting
    #endif
                    mov     al, es:[di]             ; load video buffer byte containing target pixel
                    and     al, ah                  ; mask off only the target pixel
                    mov     flag, al                ; store in flag

            END:

    #ifdef STACKING
                    pop     di
                    pop     cx
                    pop     bx
                    pop     dx
                    pop     es
                    pop     ax
    #endif
                }
                return (bool)flag;
            }

	    }

	    namespace toroid_bound {

		

	    }

    }

}

#endif