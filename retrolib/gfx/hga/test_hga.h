/**
 *
 *  @file      test_hga.h
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      11.04.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_HGA_H
#define TEST_HGA_H

#include <iostream>
#include <cassert>
#include <cmath>
#include <stdio.h>

#include "../../bios/bios_clock_services.h"
#include "../../bios/bios_video_services.h"

#include "../../memory/array.h"

#include "../point_2d.h"

#include "hga.h"
#include "hga_plot_point.h"



namespace test_hga {

        void fill_screen() {
            for (int y = 0; y < 348; y += 2) {
                for (int x = 0; x < 720; x += 2) {
                    hga::screen_bound::write_pixel(x, y, hga::colour::white);
                }
            }
        }

        void cross_hairs() {
            for (int y = 0; y < 348; ++y) {
                    hga::screen_bound::write_pixel(360, y, hga::colour::white);
            }
            for (int x = 0; x < 720; ++x) {
                    hga::screen_bound::write_pixel(x, 174, hga::colour::white);
            }
        }

        void black_diagonals() {
            int x = 12;
            for (int y = 0; y < 348; ++y) {
                    hga::screen_bound::write_pixel(x, y, hga::colour::black);
                    hga::screen_bound::write_pixel(720 - x, y, hga::colour::black);
                    x += 2;
            }
        }

        void run() {

            std::cout
                << bios::video_adapter_names[bios::detect_video_adapter_type()] << " "
                << hga::mode_names[hga::detect_mode()] << '\n'
                << "\ntest Hercules...\n";
            
            uint32_t time = 0;
          
            // read the light pen registers
            /* {
                std::cout
                    << "\nPen regs = "
                    << hga::read_light_pen_registers() << '\n';
            }
            // print the HGA video display data area
            {
                uint8_t vdda[30];
                bios::read_VDDA((uint32_t)vdda);
                for (int i = 0; i < 30; ++i) std::cout << (int)vdda[i] << ' ';
                std::cout << std::endl;
            }*/
            // enter graphics mode
            {
                std::cout << "\nswitch to gfx mode Press <ENTER>";
                std::getchar();
                hga::graphics_mode();   
                hga::cls();
            }
            // test write_pixel and time filling screen with every other pixel
            {
                bios::set_system_clock_counter(0);
                cross_hairs();
                time = bios::read_system_clock_counter();
                //fill_screen();
                time = bios::read_system_clock_counter() - time;
                //black_diagonals();
                //std::getchar();
            }
            // test plot pixels from array of dword points
            {
                uint32_t data[16];
                jtl::union_point_t point;
                int x = 0;
                for (int y = 0; y < 16; ++y) { // build multi-point data array
                    point.p.y = 100 + y;
                    point.p.x = 100 - x;
                    x += 2;
                    data[y] = point.dword;
                    hga::screen_bound::plot_point(point.dword);
                }
                //hga::screen_bound::plot_multi_point(data, 16);
                std::getchar();
            }
            //swap buffers
            {
                uint32_t data[16];
                jtl::union_point_t point;
                int x = 0;
                for (int y = 0; y < 16; ++y) { // build multi-point data array
                    point.p.y = 100 + y;
                    point.p.x = 100 + x;
                    x += 2;
                    data[y] = point.dword;
                }
                hga::cls(0);
                hga::cls(1);
                hga::screen_bound::plot_multi_point(data, 16, 1);
                hga::swap_buffers();
                std::getchar();
                hga::screen_bound::unplot_multi_point(data, 16, 1);
                hga::swap_buffers();
            }
            // is_plot_point
            {
                hga::cls(0);
                cross_hairs(); // y = 348 x = 174
                jtl::union_point_t point(0, 0);
                assert(!hga::screen_bound::is_plot_point(point.dword));
                hga::screen_bound::plot_point(point.dword);
                assert(hga::screen_bound::is_plot_point(point.dword));
                /*
                for (int y = 0; y < 348; ++y) {
                    assert(!hga::screen_bound::is_plot_point(360, y));
                }
                for (int x = 0; x < 720; ++x) {
                    assert(!hga::screen_bound::is_plot_point(x, 174));
                }*/
            }
            // return to text mode
            {
                std::getchar();
                hga::text_mode();
                std::cout << std::dec << "time = " << time << '\n';
                perror("error:");
                
            }

            std::cout << "success!\n";

        }

}

#endif