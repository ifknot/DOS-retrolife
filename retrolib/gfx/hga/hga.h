/**
 *
 *  @file      hga.h
 *  @brief     Hercules utilities
 * @details    Most MDA clones implement some form of Hercules-compatible graphics. The main differences for a Hercules-compatible card are:
 * + Writing to port 03BFh enables extra bits in the Mode Control register at 03B8h:
 *              Set bit 0 of 3BFh to enable bit 1 of 3B8h
 *              Set bit 1 of 3BFh to enable bit 7 of 3B8h and the second 32k of RAM ("Full" mode).
 * + Writing to port 03B8h has these extra effects (assuming the appropriate bits have previously been enabled):
 *              If bit 1 is set, graphics mode is selected.
 *              If bit 7 is set, the graphics frame buffer is at 0B8000h. Otherwise it's at 0B000h.
 * + In "full" mode, an Hercules card occupies memory between 0B0000h and 0BFFFFh, for two frame buffers.
 * + In "half" mode, only one frame buffer is present, from 0B0000h to 0B7FFFh; this allows the card to be used in a dual-head configuration.
 * + Reading from port 03BAh returns vertical sync in bit 7, and a card ID in bits 6-4:
 *              000: Hercules
 *              001: Hercules Plus
 *              101: Hercules InColor
 *              111: Unknown clone (see below)
 * @note Only trust this ID once you've checked that there's a vertical sync present; if bit 7 is the same for 32768 reads in succession, then there isn't.
 * + Some Hercules cards support a light pen.
 *              Port 3BAh bit returns the lightpen sensor status.
 *      Port 3BBh any write resets the light pen status.
 * One card I have encountered, which appears to be a Hercules clone of Eastern European origin, has a further capability - two ROM fonts, selectable in software.
 * These options are controlled in a similar manner to other extended features in the Hercules:
 *              Bit 2 of port 3BFh must be set to enable the feature
 *              Bit 4 of port 3B8h selects which font to use.
 * The card ID in bits 6-4 of port 03BAh has all three bits set.
 *
 *  @author    Jeremy Thornton
 *  @date      11.04.2022
 *  @copyright � Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_H
#define HGA_H

#include <stdint.h>

#include "../../dos/dos_services_types.h"

#include "hga_constants.h"

#include "dos.h"

namespace hga {

        enum video_mode_t { video_mode_text, video_mode_graphics };

        uint8_t active_buffer = 0;              // 0 = default B000:000 1 = B000:8000 second display page buffer

        void cls(uint8_t buffer = 0) {
                __asm {
                    .8086
#ifdef STACKING
                    push    ax
                    push    es
                    push    di
                    push    cx
#endif
                    mov     ax, HGA_VIDEO_RAM_SEGMENT
                    test    buffer, 1               ; which buffer ?
                    jz      J0
                    add     ax, 800h                ; second buffer
    J0:             mov     es, ax
                    xor     di, di
                    mov     cx, 4000h               ; 16K words VRAM buffer 32K bytes
                    xor     ax, ax                  ; zero ax
                    cld                                             ; increment mode
                    rep     stosw                   ; clear VRAM buffer
#ifdef STACKING
                    pop     cx
                    pop     di
                    pop     es
                    pop     ax
#endif
                }
        }


        void swap_buffers() {
                __asm {
                    .8086
#ifdef STACKING
                    push dx
                    push ax
#endif
                    xor     active_buffer, 1        ; flip to other page  using xor 0 -> 1 so 1 -> 0
                    mov     dx, HGA_CONTROL_REGISTER
                    cmp     active_buffer, 1
                    je      L0
                    mov     al, 00001010b           ; screen on
                    out     dx, al
                    jmp     END
    L0:             mov     al, 10001010b           ; screen on
                    out     dx, al
    
    END:            
                    
#ifdef STACKING
                    pop     ax
                    pop     dx
#endif
                }
        }

        void select_buffer(uint8_t buffer) {
                active_buffer = buffer;
                __asm {
                    .8086
#ifdef STACKING
                    push dx
                    push ax
#endif
                    mov     dx, HGA_CONTROL_REGISTER
                    cmp     buffer, 1
                    je      L0
                    mov     al, 00001010b           ; screen on graphics mode page 1
                    out     dx, al
                    jmp     END
    L0:             mov     al, 10001010b           ; screen on graphics mode page 2
                    out     dx, al
        
    END:            
                    
#ifdef STACKING
                    pop     ax
                    pop     dx
#endif
                }
        }

        /**
         *  @brief  program CRTC fortext mode
         *  @details Since the Hercules card(s) use the same CRTC 6845 processor as the IBM card(s), the internal registers of the 6845 and theri meaning are identical to the IBM MDA.
         *  The index register and data register are also located at the same address and the following values must be assigned to the various registers in the text and graphics modes respectibvely.
         *  @note values as per Hercules recommended
         */
        void text_mode() {
                const uint8_t text_mode_6845[32] = {
                // reg  value   meaning
                    0,      97, // horizontal character seeded
                    1,      80, // horizontal character displayed
                    2,      82, // horizontal sync signal after character
                    3,      15, // horizontal sync signal width
                    4,      25, // vertical character seeded
                    5,       6, // vertical character justified
                    6,      25, // vertical character displayed
                    7,      25, // vertical sync signal after character
                    8,       2, // interlace mode
                    9,      13, // scan-lines per line
                    10,     11, // starting line of blinking cursor
                    11,     12, // ending line of blinking cursor
                    12,  0, // hi byte of screen page start address
                    13,      0, // lo byte of screen page start address
                    14,      0, // hi byte of blinking cursor character address
                    15,      0  // lo byte of blinking cursor character address
                //  16      reserved
                //  17      reserved
                };
                __asm {
                    .8086
#ifdef STACKING
                    push    dx
                    push    ax
                    push    si
                    push    cx
#endif
                    // enable text mode via the Hercules control register 3B8h
                    // bit 0 = 0 disable bit 1 of control register 03B8h
                    // bit 1 = 0 disable second 32k of RAM ("Full" mode)
                    mov     dx, HGA_CONFIG_REGISTER
                    mov     al, 00000000b                           ; text mode single display page
                    out     dx, al

                    // program text mode with screen off
                    // bit 1 = 0 set text mode
                    // bit 3 = 0 screen off
                    // bit 5 = 0 blink off
                    // bit 7 = 0 display page 1
                    mov     dx, HGA_CONTROL_REGISTER
                    mov     al, 00000000b                           ; enter text "half" mode single display frame(mimic MDA)
                    out     dx, al

                    // program the CRTC for text mode
                    lea     si, text_mode_6845
                    cld                                                                     ; increment mode
                    mov     cx, 16                                  ; 16 registers of the 6845
                    mov     dx, CRTC_ADDRESS_PORT

    L0:             lodsw                                           ; al = register ah = data
                    out     dx, ax                                  ; write data to 6845 register
                    loop    L0

                    // screen on
                    mov     dx, HGA_CONTROL_REGISTER
                    mov     al, 00001000b                           ; bit 3 = 0 screen on text mode page 1
                    out     dx, al
#ifdef STACKING
                    pop     cx
                    pop     si
                    pop     ax
                    pop     dx
#endif    
                }
        }

        /**
         *  @brief  program CRTC for graphics mode
         *  @details Since the Hercules card(s) use the same CRTC 6845 processor as the IBM card(s), the internal registers of the 6845 and theri meaning are identical to the IBM MDA.
         *  The index register and data register are also located at the same address and the following values must be assigned to the various registers in the text and graphics modes respectibvely.
         *  @note values as per Hercules recommended
         */
        void graphics_mode() {
                active_buffer = 0;
                const uint8_t graphics_mode_6845[32] = {
                        // reg  value   meaning
                                0,      53, // horizontal character total 54 (0..53)
                                1,      45, // horizontal character displayed
                                2,      46, // horizontal sync signal after character
                                3,       7, // horizontal sync signal width
                                4,      91, // vertical character total 92 (0..91)
                                5,       2, // vertical character justified 2 scan lines
                                6,      87, // vertical character displayed rows (348 lines)
                                7,      87, // vertical sync signal after character
                                8,       2, // interlace mode
                                9,       3, // scan-lines per char 4 (0..3)
                                10,      0, // starting line of blinking cursor
                                11,      0, // ending line of blinking cursor
                                12,      0, // hi byte of screen page start address
                                13,      0, // lo byte of screen page start address
                                14,      0, // hi byte of blinking cursor character address
                                15,      0  // lo byte of blinking cursor character address
                        //  16      reserved
                        //  17      reserved
                };
                __asm {
                        .8086
#ifdef STACKING
                        push    dx
                        push    ax
                        push    si
                        push    cx
#endif

                        // enable graphics mode via the Hercules control register 3B8h
                        // Set bit 0 of 3BFh to enable bit 1 of 3B8h
                        // Set bit 1 of 3BFh to enable bit 7 of 3B8h and the second 32k of RAM ("Full" mode).
                        // bit 0 = 0 enable bit 1 of control register 03B8h
                        // bit 1 = 0 disable second 32k of RAM ("Full" mode)
                        mov             dx, HGA_CONFIG_REGISTER
                        mov             al, 00000011b                   ; enable graphics "full" mode with 2 frame buffers
                        out             dx, al

                        // program graphics mode with screen off
                        // bit 1 = 1 set graphics mode
                        // bit 3 = 0 screen off
                        // bit 5 = 0 blink off
                        // bit 7 = 0 display page 1
                        mov             dx, HGA_CONTROL_REGISTER
                        mov             al, 00000010b                   ; enter graphics mode display page 1
                        out             dx, al

                        // program the CRTC for graphics mode
                        lea             si, graphics_mode_6845
                        cld                                                             ; increment mode
                        mov             cx, 16                                  ; 16 registers of the 6845
                        mov             dx, CRTC_ADDRESS_PORT

        L0:             lodsw                                                   ; al = register ah = data
                        out             dx, ax                                  ; write data to 6845 register
                        loop    L0

                        // screen on
                        mov             dx, HGA_CONTROL_REGISTER
                        mov             al, 00001010b                   ; bit 3 = 0 screen on graphics mode page 1
                        out             dx, al
#ifdef STACKING
                        pop     cx
                        pop     si
                        pop     ax
                        pop     dx
#endif
                }
        }

        /**
        *  @brief  the 6845 CRTC's Light Pen High and Low registers (10h and 11h) in the high and low bytes
        *  @retval  - High and Low registers
        */
        uint16_t read_light_pen_registers() {
                uint16_t pen_regs = 0;
                __asm {
                        .8086
#ifdef STACKING
                        push dx
                        push ax
#endif
                        mov     dx, CRTC_LIGHT_PEN_RESET        ; reset the CRTC light pen latch
                        out     dx, al                                          ; writing anything to this port resets the light pen

                        mov     dx, CRTC_STATUS_PORT            ; wait for start of vertical retrace
        L1:             in      al, dx                                          ; read status port
                        test    al, 80h                                         ; is horizontal retrace active?
                        jnz     L1                                                      ; retrace still active

        L2:             in      al, dx                                          ; read status port again
                        test    al, 80h                                         ; is horizontal retrace active?
                        jz      L2                                                      ; not yet

                        cli                                                                     ; disable interupts
        L3:             in      al, dx                                          ; read status port again
                        test    al, 80h                                         ; is horizontal retrace active ?
                        jnz             L3                                                      ; wait for it to to finish

                        mov     dx, CRTC_LIGHT_PEN_LATCH        ; latch the light pen register counter
                        out     dx, al                                          ; writing anything captures
                        sti                                                                     ; re-enable interupts

                        mov     dx, CRTC_ADDRESS_PORT
                        mov     al, 10h                                         ; Light Pen high register number
                        out     dx, al                                          ; latch high register

                        mov     dx, CRTC_DATA_PORT
                        in      al, dx                                          ; high reg in al
                        mov     ah, al                                          ; copy to ah

                        mov     dx, CRTC_ADDRESS_PORT
                        mov     al, 11h                                         ; Light Pen low register number
                        out             dx, al                                          ; latch low register

                        mov     dx, CRTC_DATA_PORT
                        in      al, dx                                          ; low reg in al

                        mov     pen_regs, ax
#ifdef STACKING
                        pop     ax
                        pop     dx
#endif
                }
                return pen_regs;
        }

        /**
          *  @brief  Determine Hercules Vidoe Mode
          *      @note 1. The ROM BIOS does not keep track of a Hercules Graphic Adapter video mode
          *  @details Whilst it is possible to infer the video mode from the Video Display Data Area variables this approach presumes these variables have been correctly updated.
          *  However, it is possible to us the light pen registers to determine video modes on Hercules graphics adapters.
          *  Latching the 6845 CRTC's Light Pen High and Low registers (10h and 11h) at the start of vertical retrace will return different values for the CRTC's address counter
          *  depending on the current mode - at least 7D0h (2000) in alphanumeric mode and 0FBh (251) in graphics mode.
          *  @note 2. The values are somewhat larger in reality but provides reliable upper and lower bounds.
          *  @note 3. The imprecision makes detection less reliable on HCG+ and InColor cards due to differing values for the differing character sizes these cards offer
          *
          *  @retval  - video_mode_t text_mode (0) or graphics_mode (1)
          */
        video_mode_t detect_mode() {
                return read_light_pen_registers() < 2000 ? video_mode_graphics : video_mode_text;
        }

}

#endif