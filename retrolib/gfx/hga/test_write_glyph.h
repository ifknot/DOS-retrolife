/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_WRITE_GLYPH_H
#define TEST_WRITE_GLYPH_H

#include <cassert>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include "../../bios/bios_clock_services.h"

#include "hga_graphics.h"
#include "hga_write_glyph.h"

namespace test_write_glyph {

        void run() {
            uint32_t time = 0;
            std::cout << "test_write_glyph... \n";
            {
                    uint8_t v[64] = { // checkerboard pixels
                        0xAA, 0xAA, 0xAA, 0xAA,
                        0x55, 0x55, 0x55, 0x55,
                        0xAA, 0xAA, 0xAA, 0xAA,
                        0x55, 0x55, 0x55, 0x55,
                        0xAA, 0xAA, 0xAA, 0xAA,
                        0x55, 0x55, 0x55, 0x55,
                        0xAA, 0xAA, 0xAA, 0xAA,
                        0x55, 0x55, 0x55, 0x55,
                        0xAA, 0xAA, 0xAA, 0xAA,
                        0x55, 0x55, 0x55, 0x55,
                        0xAA, 0xAA, 0xAA, 0xAA,
                        0x55, 0x55, 0x55, 0x55,
                        0xAA, 0xAA, 0xAA, 0xAA,
                        0x55, 0x55, 0x55, 0x55,
                        0xAA, 0xAA, 0xAA, 0xAA,
                        0x55, 0x55, 0x55, 0x55
                    };
                    uint8_t sq[64] = { // 62x62 box
                        0x00, 0x00, 0x00, 0x00,
                        0x7F, 0xFF, 0xFF, 0xFE,
                        0x40, 0x00, 0x00, 0x02,
                        0x40, 0x00, 0x00, 0x02,
                        0x40, 0x00, 0x00, 0x02,
                        0x40, 0x00, 0x00, 0x02,
                        0x40, 0x00, 0x00, 0x02,
                        0x40, 0x00, 0x00, 0x02,
                        0x40, 0x00, 0x00, 0x02,
                        0x40, 0x00, 0x00, 0x02,
                        0x40, 0x00, 0x00, 0x02,
                        0x40, 0x00, 0x00, 0x02,
                        0x40, 0x00, 0x00, 0x02,
                        0x40, 0x00, 0x00, 0x02,
                        0x7F, 0xFF, 0xFF, 0xFE,
                        0x00, 0x00, 0x00, 0x00
                    };
                    uint8_t a[8] = { // letter A
                            0, 0x38, 0x44, 0x44, 0x44, 0x7C, 0x44, 0x44
                    };
                    getchar();
                    hga::graphics_mode();
                    hga::cls();
                    time = bios::read_system_clock_counter();
                    for (int y = 0; y < 43; ++y) {
                        for (int x = 0; x < 90; ++x) {
                            hga::screen_bound::write_glyph_8x8(x, y, a);
                        }
                    }
                    time = bios::read_system_clock_counter() - time;
                    //hga::screen_bound::write_glyph_32x16(10, 10, v);
                    //hga::screen_bound::write_glyph_32x16(12, 12, sq);

                    //for (int y = 0; y < 23; ++y) {
                        //for (int x = 0; x < 22; ++x) {
                            //hga::screen_bound::write_glyph_32x16(x, y, sq);
                        //}
                    //}

                    getchar();
                    hga::text_mode();
                    std::cout << std::dec << "time = " << time / TICKS_PER_SECOND << '\n';
                }
                std::cout << "success!\n";
        }

}

#endif