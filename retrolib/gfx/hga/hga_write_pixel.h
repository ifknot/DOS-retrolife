/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_WRITE_PIXEL_H
#define HGA_WRITE_PIXEL_H

#include "hga_constants.h"

namespace hga {

	namespace screen_bound {

		/**
        *  @brief write pixel display page (default 0), clipping to fit within the screen bounds
        *  @param x      - screen x coordinate, (0,0) top-left
        *  @param y      - screen y coordinate, (719,347) bottom right
        *  @param colour - background 0 foreground 1
        *  @param buffer - (default) 0 first screen buffer 1 second screen buffer
        */
        inline void write_pixel(size_type x, size_type y, colour_t colour, uint8_t buffer = 0) {
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
                // bit shifting * 90
                and     ax, 0FFFCh              ; mask out bank selection bits
                mov     bx, ax                  ; copy y
                //shr     ax, 1                 ; calculate y / 4
                //shr     ax, 1                 ; 8086 limited to single step shifts

                // (y / 4) * 80
                // simplifies to y * 20
                //shl     ax, 1                 ; 8086 shift left 4 times
                //shl     ax, 1                 ; y * 16
                shl     ax, 1
                shl     ax, 1
                mov     cx, ax                  ; copy y
                shl     ax, 1                   ; 8086 shift left 2 times
                shl     ax, 1                   ;
                add     ax, cx                  ;
                // (y / 4) * 10
                // simplifies to (y / 2) * 4
                //shr     bx, 1       ; calculate y / 4
                shr     bx, 1                   ; 8086 limited to single step shifts
                //shl     bx, 1
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
                mov     al, 01111111b           ; load al with pixel mask
                mov     ah, colour              ; load ah with a single pixel at msb (e.g. white 10000000)
                ror     al, cl                  ; roll mask around by x mod 8
                shr     ah, cl                  ; shift single bit along by x mod 8

#ifdef SYNCHRONISED     // will need al so cost an extra mov reg, reg to copy into cl
                mov     cl, al                  ; copy mask byte
                mov     dx, CGA_STATUS_REG      ; CGA status reg
        S0:     in      al, dx                  ; read status
                test    al, 1000b               ; is bit 3 set ? (in a vertical retrace interval)
                jnz     S0                      ; yes, keep waiting
        S1:     in      al, dx                  ; read status
                test    al, 1000b               ; is bit 3 set ? (just started a vertical retrace interval)
                jnz     S1                      ; no, keep waiting

                and     es:[di], cl             ; mask out the pixel bit
#else
                and     es:[di], al             ; mask out the pixel bit
#endif
                or      es:[di], ah             ; plot point

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
        }

	}

	namespace toroid_bound {

	}

}

#endif