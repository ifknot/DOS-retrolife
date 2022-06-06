/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_PLOT_MULTI_POINT_H
#define HGA_PLOT_MULTI_POINT_H

#include "hga_constants.h"

namespace hga {

	namespace screen_bound {

		 void plot_multi_point(const uint32_t* point_data, uint16_t size, uint8_t buffer = 0) {
            __asm {
                .8086
#ifdef STACKING
                push    ds
                push    si
                push    ax
                push    es
                push    dx
                push    bx
                push    cx
                push    di
#endif
                lds     si, point_data          ; ds:[si] points to list of points to plot
                // NB must compile memory model large
                mov     cx, size                ; number of points to plot
                cld                             ; increment mode

        L0:     push    cx                      ; preserve cx

                mov     ax, HGA_VIDEO_RAM_SEGMENT
                test    buffer, 1               ; which buffer ?
                jz      J0
                add     ax, 800h                ; second buffer
        J0:     mov     es, ax
                lodsw                           ; load y into ax from data, then perform screen clipping
                cmp     ax, SCREEN_Y_MAX        ; compare bx with y maximum boundry
                jge     L1                      ; nothing to plot
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
                add     bx, ax                  ; + (y * 4)
#endif
                and     dx, 00000011b           ; mask off only the bank select bits (0..4)
                ror     dx, 1                   ; calculate 16-bit bank# * 2000h
                ror     dx, 1                   ; 8086 limited to single step shifts
                ror     dx, 1                   ; (y mod 4) * 2000h

                lodsw                           ; load x from data
                mov     di, ax                  ; move x into di and clip to screen bounds
                cmp     di, SCREEN_X_MAX        ; compare di with x maximum boundry
                jge     L1                     ; nothing to plot
                mov     cx, di                  ; copy of x in cx
                shr     di, 1                   ; calculate column byte x / 8
                shr     di, 1                   ; 8086 limited to single step shifts
                shr     di, 1                   ; x / 8
                add     di, bx                  ; + (y / 4) * 90
                add     di, dx                  ; + (y mod 4) * 2000h
                and     cx, 7h                  ; mask off 0111 lower bits i.e.mod 8 (thanks powers of 2)
                mov     ah, 10000000b           ; load ah with a single pixel at msb
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
                or      es:[di], ah             ; plot point

        L1:     pop     cx                      ; restore the counter from stack
                loop    L0                      ; plot next point until all done
#ifdef STACKING
                pop     di
                pop     cx
                pop     bx
                pop     dx
                pop     es
                pop     ax
                pop     si
                pop     ds
#endif
            }
        }

	}

	namespace toroid_bound {

		

	}

}

#endif