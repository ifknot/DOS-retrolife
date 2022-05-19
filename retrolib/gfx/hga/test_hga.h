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

#include "../../bios/bios_video_services.h"
#include "../../jtl/array.h"

#include "hga.h"
#include "hga_plot_point.h"

#include "../../bios/bios_clock_services.h"

namespace test_hga {

        void fill_screen() {
            for (int y = 0; y < 348; y += 2) {
                for (int x = 0; x < 720; x += 2) {
                    hga::screen_bound::write_pixel(x, y, hga::colour::white, 1);
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
            }
            // test write_pixel and time filling screen with every other pixel
            /* {
                bios::set_system_clock_counter(0);
                cross_hairs();
                time = bios::read_system_clock_counter();
                fill_screen();
                time = bios::read_system_clock_counter() - time;
                black_diagonals();
            }*/
            // test plot pixels from array of dword points
            {
                uint32_t data[16];
                hga::union_point_t point;
                int x = 0;
                for (int y = 0; y < 16; ++y) { // build multi-point data array
                    point.word.y = 100 + y;
                    point.word.x = 100 - x;
                    x += 2;
                    data[y] = point.dword;
                }
                hga::screen_bound::plot_multi_point(data, 16);
                std::getchar();
            }
            //swap buffers
            {
                uint32_t data[16];
                hga::union_point_t point;
                int x = 0;
                for (int y = 0; y < 16; ++y) { // build multi-point data array
                    point.word.y = 100 + y;
                    point.word.x = 100 + x;
                    x += 2;
                    data[y] = point.dword;
                }
                hga::cls(0);
                hga::cls(1);
                hga::screen_bound::plot_multi_point(data, 16, 1);
                hga::swap_buffers();
                std::getchar();
                hga::screen_bound::unplot_multi_point(data, 16, 1);
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

/*

{
                        const double PI = 3.14159;

                        double w = 141;
                        double h = 141;
                        double xstep = 1;
                        double ystep = 3;
                        double delta = 70;
                        double k = 80;
                        double factor = -0.001;
                        jtl::size_t xnudge = 300;
                        jtl::size_t ynudge = 180;
                        jtl::array<jtl::size_t, 255> m;
                        m.clear();

                        double a = std::cos(PI / 4);
                        for (double y = 1; y < h; y += ystep) {
                                double e = a * y;
                                double c = y - delta;
                                c = c * c;
                                for (double x = 1; x < w; x += xstep) {
                                        double d = x - delta;
                                        double z = k * std::exp(factor * (c + d * d));
                                        jtl::size_t x1 = static_cast<jtl::size_t>(x + e);
                                        jtl::size_t y1 = static_cast<jtl::size_t>(z + e);
                                        if (y1 >= m[x1]) {
                                                m[x1] = y1;
                                                hga::screen_bound::plot_point(x1 + xnudge, ynudge - y1, hga::colour::white);
                                        }
                                }
                        }
                }

*/