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
#include <iomanip>

#include "../../bios/bios_clock_services.h"

#include "hga_graphics.h"
#include "hga_write_glyph.h"

#include "../../font8x8/font8x8_latin.h"
#include "../../font8x8/font8x8_box.h"

#include "../../memory/reverse_bits.h"

namespace test_write_glyph {

        void run() {
            uint32_t time = 0;
            std::cout << "test_write_glyph... \n";
            {
                uint8_t a[8] = { // letter A
                    0, 0x38, 0x44, 0x44, 0x44, 0x7C, 0x44, 0x44
                };

                //for (int i = 0; i < 128; ++i) jtl::reverse_bits(jtl::font8x8_basic[i], 8);
                //for (int i = 0; i < 96; ++i) jtl::reverse_bits(jtl::font8x8_ext_latin[i], 8);
                //for (int i = 0; i < 128; ++i) jtl::reverse_bits(jtl::font8x8_box[i], 8);
                
                getchar();
                hga::graphics_mode();
                hga::cls();
                time = bios::read_system_clock_counter();
                int i = 0;
                for (int y = 0; y < 43; ++y) {
                    for (int x = 0; x < 90; ++x) {
                        //hga::screen_bound::write_glyph_8x8(x, y, a);
                        //hga::screen_bound::write_glyph_8x8(x, y, jtl::font8x8_basic[i++ % 128]);
                        hga::screen_bound::write_glyph_8x8(x, y, jtl::font8x8_ext_latin[i++ % 96]);
                        //hga::screen_bound::write_glyph_8x8(x, y, jtl::font8x8_box[i++ % 128]);
                    }
                }
                time = bios::read_system_clock_counter() - time;
                    
                getchar();
                hga::cls();
                hga::text_mode();                
            }
            std::cout
                << "\nsuccess!\n"
                << std::dec << "time = " << time / TICKS_PER_SECOND << '\n';
            
        }

}

#endif