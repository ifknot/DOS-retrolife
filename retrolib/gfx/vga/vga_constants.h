/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef VGA_CONSTANTS_H
#define VGA_CONSTANTS_H

#define VGA_VIDEO_RAM_SEGMENT   0A000h
#define SC_INDEX                3C4h    // Sequence Controller Index register
#define GC_INDEX                3CEh    // Graphics Controller Index register
#define CRTC_INDEX              3D4h    // CRT Controller Index register
#define MAP_MASK                2		// Map Mask register index in SC
#define MEMORY_MODE             4		// Memory Mode register index in SC
#define MAX_SCAN_LINE           9		// Maximum Scan Line reg index in CRTC
#define START_ADDRESS_HIGH		0Ch		// Start Address High reg index in CRTC
#define UNDERLINE               14h		// Underline Location reg index in CRTC
#define MODE_CONTROL            17h		// Mode Control register index in CRTC
#define READ_MAP                4		// Read Map register index in GC
#define GRAPHICS_MODE           5		// Graphics Mode register index in GC
#define MISCELLANEOUS           6		// Miscellaneous register index in GC
#define SCREEN_WIDTH            320		// # of pixels across screen
#define SCREEN_HEIGHT           400		// # of scan lines on screen

#endif