/**
 *
 *  @brief Hercules VRAM starts at B000:0000
 *  @details The Hercules display adapter displays in both text mode and graphics mode,
 *  with a graphics resolution of 720x348 pixels, and contains enough RAM for 2 page displays.
 *  B000:0000 - B000:7FFF   First Page
 *  B000:8000 - B000:FFFF   Second Page
 *  Each display page is 32K, having the capacity to host a 4K text page and a graphics page.
 *  @note However, the 32K per buffer is not contiguous but rather split into 4 banks of 8K VRAM each
 *  that map to 4 consecutive screen lines before the 5th line starts back in bank 0 but 90 bytes in.
 *  So each group of 4 lines is separated by 2000h bytes.
 *  
 *  The screen dimensions of 720x348 are only evenly divisible 4x4 pixel blocks
 *  For "glyph space" I have chosen an 8x8 pixel block grid giving 90x43.5 glyph locations
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

		inline void write_glyph_8x8(uint16_t x, uint16_t y, const uint8_t* bytes, uint8_t buffer = 0) {
            __asm {
		.8086
                shl     x, 1                    ; convert x glyph column to pixel location
                shl     x, 1                    ; * 8
                shl     x, 1                    ; 8086 limited to single step shifts
                    
                shl     y, 1                    ; convert y glyph row to pixel location
                shl     y, 1
                shl     y, 1

		        lds     si,     bytes		            ; ds:[si] points to list of 8 glyph data bytes to write

		        mov     ax,     HGA_VIDEO_RAM_SEGMENT
                test    buffer, 1               ; which buffer ?
                jz      J0                      ; B000:0000 - B000 : 7FFF   First Page
                add     ax, 800h                ; B000:8000 - B000 : FFFF   Second Page
        J0:     mov     es, ax			        ; es points to screen segment

		        mov     ax, y                   ; load y into ax then perform screen clipping
		        cmp     ax, SCREEN_Y_MAX        ; compare ax with y maximum boundry
                jge     END                     ; nothing to plot                
		        shr     ax, 1                   ; calculate y / 4
                shr     ax, 1                   ; 8086 limited to single step shifts
                mov     cl, BYTES_PER_LINE
                mul     cl                      ; calculate(y / 4) * 90
		        
		        mov     di, x                   ; load x into di and clip to screen bounds
                cmp     di, SCREEN_X_MAX        ; compare di with x maximum boundry
                jge     END                     ; nothing to plot
                shr     di, 1                   ; calculate column byte x / 8
                shr     di, 1                   ; 8086 limited to single step shifts
                shr     di, 1                   ; x / 8
                add     di, ax                  ; + (y / 4) * 90

#ifdef SYNCHRONISED                    
                mov     dx, HGA_STATUS_REG      ; CGA status reg
        S0:     in      al, dx                  ; read status
                test    al, 1000b               ; is bit 3 set ? (in a vertical retrace interval)
                jnz     S0                      ; yes, keep waiting
        S1:     in      al, dx                  ; read status
                test    al, 1000b               ; is bit 3 set ? (just started a vertical retrace interval)
                jnz     S1                      ; no, keep waiting              
#endif
                lodsb                           ; load 8 pixels strip glyph row 0 into al
                mov     es:[di], al             ; store row 0 bank 0 as guaranteed bank zero start in glyph space coords
                lodsb                           ; load 8 pixels strip glyph row 1 into al
                mov     es:[di + 2000h], al     ; store row 1 bank 1
                lodsb                           ; load 8 pixels strip glyph row 2 into al
                mov     es:[di + 4000h], al     ; store row 2 bank 2
                lodsb                           ; load 8 pixels strip glyph row 3 into al
                mov     es:[di + 6000h], al     ; store row 3 bank 3

                add     di, 90                  ; add 90 bytes next line for all 4 banks

                lodsb                           ; load 8 pixels strip glyph row 4 into al
                mov     es : [di] , al          ; store row 4 bank 0
                lodsb                           ; load 8 pixels strip glyph row 5 into al
                mov     es : [di + 2000h], al   ; store row 5 bank 1
                lodsb                           ; load 8 pixels strip glyph row 6 into al
                mov     es : [di + 4000h], al   ; store row 6 bank 2
                lodsb                           ; load 8 pixels strip glyph row 7 into al
                mov     es : [di + 6000h], al   ; store row 7 bank 3

		END:
			}
		}

        inline void write_glyph_32x16(uint16_t x, uint16_t y, uint8_t* bytes, uint8_t buffer = 0) {
            uint16_t ox;
            __asm {
				.8086
                shl     x, 1                    ; convert x glyph column to pixel location
                shl     x, 1                    ; * 8
                shl     x, 1                    ; 8086 limited to single step shifts
                    
                shl     y, 1                    ; convert y glyph row to pixel location
                shl     y, 1
                shl     y, 1

		        lds     si, bytes               ; ds: [si] points to list of 64 glyph data bytes to write

		        mov     ax, HGA_VIDEO_RAM_SEGMENT
                test    buffer, 1               ; which buffer ?
                jz      J0                      ; B000:0000 - B000 : 7FFF   First Page
                add     ax, 800h                ; B000:8000 - B000 : FFFF   Second Page
        J0:     mov     es, ax			        ; es points to screen segment

                mov     cx, 16                  ; 16 rows 
        Y0:     push    cx

                mov     ax, x
                mov     ox, ax

                mov     cx, 4                   ; 4 bytes i.e. 32x32 pixels
        X0:     push    cx 

		        mov     ax, y                  	; load y into ax then perform screen clipping
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
		        mov     di, ox                  ; load x into di and clip to screen bounds
                cmp     di, SCREEN_X_MAX        ; compare di with x maximum boundry
                jge     END                     ; nothing to plot
                
                shr     di, 1                   ; calculate column byte x / 8
                shr     di, 1                   ; 8086 limited to single step shifts
                shr     di, 1                   ; x / 8
                add     di, ax                  ; + (y / 4) * 90
                add     di, dx                  ; + (y mod 4) * 2000h
                
                //lodsb                           ; load al with pixel data 
           
#ifdef SYNCHRONISED    
                // not needed w movsb ---> xchg    ah, al                  ; copy data byte
                mov     dx, CGA_STATUS_REG      ; CGA status reg
        S0:     in      al, dx                  ; read status
                test    al, 1000b               ; is bit 3 set ? (in a vertical retrace interval)
                jnz     S0                      ; yes, keep waiting
        S1:     in      al, dx                  ; read status
                test    al, 1000b               ; is bit 3 set ? (just started a vertical retrace interval)
                jnz     S1                      ; no, keep waiting
                // not needed w movsb ---> xchg    ah, al
#endif
                //stosb
		movsb

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
