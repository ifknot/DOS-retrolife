/**
 *
 *  @file               hga_plot_point.h
 *  @brief              Plot a point in Hecules Graphics Mode
 *  @details    HGA Graphics Mode pixel-addressable graphics mode at 720x348 (two rows of pixels are lost since the dimensions must be divisible by four for technical reasons).
 *      VRAM:           64K
 *      Pixel Ratio 1:1.55 on a standard 4:3 display.
 *  Segments:   B000:0000 - B000:7FFF   First Page
 *              B000:8000 - B000:FFFF   Second Page
 *  The HGA has 64K of Video RAM and each display page is 32K, having the capacity to host a 4K text page and a graphics page.
 *  @note The display page is (once enabled) selectable
 *  Layout:     An unusual layout of 4 interleaved scan lines, packed pixel.
 *  The 32K VRAM of each display page is divided into 4 x 8K blocks.
 *              Block 1 divisible by 4 then + 0 (0, 4, 8, 12..)
 *              Block 2 divisible by 4 then + 1 (1, 5, 9, 13..)
 *              Block 3 divisible by 4 then + 2 (2, 6, 10, 14..)
 *              Block 4 divisible by 4 then + 3 (3, 7, 11, 15..)
 *
 *              Each scan line is 90-bytes long and there are 348 scan lines (2 lines unused in each block)
 *      Each byte contains 8 pixels
 *          (31,320 total pixel bytes):
 *          ╓7┬6┬5┬4┬3┬2┬1┬0╖
 *          ║ │ │ │ │ │ │ │ ║
 *          ╙╥┴╥┴╥┴╥┴╥┴╥┴╥┴╥╜  bits mask
 *           ║ ║ ║ ║ ║ ║ ║ ╚══► 0:  01H  eighth pixel in byte
 *           ║ ║ ║ ║ ║ ║ ╚════► 1:  02H  seventh pixel in byte
 *           ║ ║ ║ ║ ║ ╚══════► 2:  04H  sixth pixel in byte
 *           ║ ║ ║ ║ ╚════════► 3:  08H  fifth pixel in byte
 *           ║ ║ ║ ╚══════════► 4:  10H  fourth pixel in byte
 *           ║ ║ ╚════════════► 5:  20H  third pixel in byte
 *           ║ ╚══════════════► 6:  40H  second pixel in byte
 *           ╚════════════════► 7:  80H  first pixel in byte
 *                                       0=black; 1=white*
 *
 *  @author    Jeremy Thornton
 *  @date      28.04.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_GRAPHICS_H
#define HGA_GRAPHICS_H

#include "hga_cls.h"
#include "hga_constants.h"
#include "hga_count_plot_multi_point.h"
#include "hga_count_relative_plot_multi_point.h"
#include "hga_is_plot_point.h"
#include "hga_plot_functors.h"
#include "hga_plot_multi_point.h"
#include "hga_plot_point.h"
#include "hga_select_buffer.h"
#include "hga_swap_buffers.h"
#include "hga_unplot_multi_point.h"
#include "hga_unplot_point.h"
#include "hga_video_mode.h"
#include "hga_write_pixel.h"

#endif