/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      29.08.2022
 *  @copyright � Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MDA_MODE7_DRAW_VERTICAL_LINE_H
#define MDA_MODE7_DRAW_VERTICAL_LINE_H

#include "mda_mode7_constants.h"

namespace mda {

	namespace mode7 {

		namespace screen_bound {

			void draw_vertical_line(size_type x1, size_type y1, size_type x2, size_type y2, char ascii = FULL_BLOCK, attrib_t attrib = attribute::normal) {
				__asm {
					.8086

					mov		ax, x1
					cmp		ax, x2					; it has to be a vertical line
					jne		END						; nothing to draw

					mov		ax, MDA_VIDEO_RAM_SEGMENT
					mov		es, ax					; ES:DI will point to x,y screen byte 
					mov		bx, x1					; load x into bx then perform screen clipping
					cmp     bx, SCREEN_X_MAX        ; compare bx with x maximum boundry
					jge     END						; nothing to draw
					mov		ax, y1					; load y into ax then perform screen clipping
					cmp     ax, SCREEN_Y_MAX        ; compare ax with y maximum boundry
					jge     END                     ; nothing to draw

					mov		cx, y2					; x1,y1 is onscreen x1 = x2 so clip y2
					cmp		cx, SCREEN_Y_MAX		; compare with boundry
					jl		J1						; within screen width
					sub		cx, SCREEN_Y_MAX		; clip to screen
					sub		y2, cx					; store clipped y2
J1:

#ifdef ENABLE_MUL
					mov     cl, BYTES_PER_LINE
					mul     cl						; calculate y * 80 i.e. AX * 160 bytes
					mov		di, ax
#else		
					shl		ax, 1					; on 8086 this bitwise multiplication is faster than mul 
					shl		ax, 1					; y * 80 = (y * 16) + (y * 64)
					shl		ax, 1					; 8086 limited to single step shifts
					shl		ax, 1					; y * 16
					mov		di, ax					; copy result
					shl		ax, 1
					shl		ax, 1					; y * 64
					add		di, ax					; di = y * 80
#endif				
					shl		bx, 1					; x * 2 as 2 bytes per character cell
					add		di, bx					; di = (y * 80 ) + x
					mov		al, ascii
					mov		ah, attrib				; AX now has atrrib:ascii
					mov		es:[di], ax
END:
				}
			}

		}

	}

}


#endif