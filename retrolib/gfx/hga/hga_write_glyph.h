/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_WRITE_GLYPH_H
#define HGA_WRITE_GLYPH_H

#include <stdint.h>

#include "hga_constants.h"

namespace hga {

	namespace screen_bound {

		inline void write_glyph_8x8(uint16_t x, uint16_t y, uint8_t* bytes, uint8_t buffer = 0) {
            __asm {
				.8086
                shl     x, 1                    ; convert x to pixel location
                shl     x, 1                    ; * 8
                shl     x, 1                    ; 8086 limited to single step shifts

                shl     y, 1
                shl     y, 1
                shl     y, 1

				lds     si, bytes				; ds:[si] points to list of bytes to write

				mov     ax, HGA_VIDEO_RAM_SEGMENT
                test    buffer, 1               ; which buffer ?
                jz      J0
                add     ax, 800h                ; second buffer
        J0:     mov     es, ax					; es points to screen segment

                mov     cx, 8                   ; 8 rows of 1 byte
        Y0:     push    cx                      ; save row count            
				mov     ax, y                   ; load y into ax then perform screen clipping
				cmp     ax, SCREEN_Y_MAX        ; compare ax with y maximum boundry
                jge     END                     ; nothing to plot
                mov     dx, ax                  ; copy y
				shr     ax, 1                   ; calculate y / 4
                shr     ax, 1                   ; 8086 limited to single step shifts
                mov     cl, BYTES_PER_LINE
                mul     cl                      ; calculate(y / 4) * 90
				and     dx, 00000011b           ; copy of y mask off only the bank select bits (0..4)
                ror     dx, 1                   ; calculate 16-bit bank# * 2000h
                ror     dx, 1                   ; 8086 limited to single step shifts
                ror     dx, 1                   ; (y mod 4) * 2000h
				mov     di, x                   ; load x into di and clip to screen bounds
                cmp     di, SCREEN_X_MAX        ; compare di with x maximum boundry
                jge     END                     ; nothing to plot
                
                shr     di, 1                   ; calculate column byte x / 8
                shr     di, 1                   ; 8086 limited to single step shifts
                shr     di, 1                   ; x / 8
                add     di, ax                  ; + (y / 4) * 90
                add     di, dx                  ; + (y mod 4) * 2000h
           
#ifdef SYNCHRONISED    
                xchg    ah, al                  ; copy data byte
                mov     dx, CGA_STATUS_REG      ; CGA status reg
        S0:     in      al, dx                  ; read status
                test    al, 1000b               ; is bit 3 set ? (in a vertical retrace interval)
                jnz     S0                      ; yes, keep waiting
        S1:     in      al, dx                  ; read status
                test    al, 1000b               ; is bit 3 set ? (just started a vertical retrace interval)
                jnz     S1                      ; no, keep waiting
                xchg    ah, al
#endif
                movsb                           ; write glyph byte for this row
                inc     y                           
                pop     cx                      ; load row count
                loop    Y0                      ; next row

		END:
			}
		}

        inline void write_glyph_32x16(uint16_t x, uint16_t y, uint8_t* bytes, uint8_t buffer = 0) {
            uint16_t ox;
            __asm {
				.8086
                shl     x, 1                    ; convert x to pixel location
                shl     x, 1                    ; * 8
                shl     x, 1                    ; 8086 limited to single step shifts
                shl     x, 1
                shl     x, 1

                shl     y, 1
                shl     y, 1
                shl     y, 1
                shl     y, 1

				lds     si, bytes				; ds:[si] points to list of bytes to write

				mov     ax, HGA_VIDEO_RAM_SEGMENT
                test    buffer, 1               ; which buffer ?
                jz      J0
                add     ax, 800h                ; second buffer
        J0:     mov     es, ax					; es points to screen segment

                mov     cx, 16                  ; 16 rows 
        Y0:     push    cx

                mov     ax, x
                mov     ox, ax

                mov     cx, 4                   ; 4 bytes i.e. 32x32 pixels
        X0:     push    cx 

				mov     ax, y                  ; load y into ax then perform screen clipping
				cmp     ax, SCREEN_Y_MAX        ; compare ax with y maximum boundry
                jge     END                     ; nothing to plot
                mov     dx, ax                  ; copy y
				shr     ax, 1                   ; calculate y / 4
                shr     ax, 1                   ; 8086 limited to single step shifts
                mov     cl, BYTES_PER_LINE
                mul     cl                      ; calculate(y / 4) * 90
				and     dx, 00000011b           ; copy of y mask off only the bank select bits (0..4)
                ror     dx, 1                   ; calculate 16-bit bank# * 2000h
                ror     dx, 1                   ; 8086 limited to single step shifts
                ror     dx, 1                   ; (y mod 4) * 2000h
				mov     di, ox                   ; load x into di and clip to screen bounds
                cmp     di, SCREEN_X_MAX        ; compare di with x maximum boundry
                jge     END                     ; nothing to plot
                
                shr     di, 1                   ; calculate column byte x / 8
                shr     di, 1                   ; 8086 limited to single step shifts
                shr     di, 1                   ; x / 8
                add     di, ax                  ; + (y / 4) * 90
                add     di, dx                  ; + (y mod 4) * 2000h
                
                lodsb                           ; load al with pixel data 
           
#ifdef SYNCHRONISED    
                xchg    ah, al                  ; copy data byte
                mov     dx, CGA_STATUS_REG      ; CGA status reg
        S0:     in      al, dx                  ; read status
                test    al, 1000b               ; is bit 3 set ? (in a vertical retrace interval)
                jnz     S0                      ; yes, keep waiting
        S1:     in      al, dx                  ; read status
                test    al, 1000b               ; is bit 3 set ? (just started a vertical retrace interval)
                jnz     S1                      ; no, keep waiting
                xchg    ah, al
#endif
                stosb

                add     ox, 8
                pop     cx
                loop    X0

                inc     y
                pop     cx
                loop    Y0

		END:
			}
		}

	}

}

#endif