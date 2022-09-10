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
#include "../../memory/data_vector.h"

#include "../gfx_point_2d.h"
#include "../gfx_point_vector_2d.h"

#include "graphics/hga_graphics.h"

using namespace hga::graphics;

namespace test_hga {

        void fill_screen() {
            for (int y = 0; y < 348; y += 2) {
                for (int x = 0; x < 720; x += 2) {
                   screen_bound::write_pixel(x, y, colour::white);
                }
            }
        }

        void cross_hairs() {
            for (int y = 0; y < 348; ++y) {
                     screen_bound::write_pixel(360, y,  colour::white);
            }
            for (int x = 0; x < 720; ++x) {
                     screen_bound::write_pixel(x, 174,  colour::white);
            }
        }

        void black_diagonals() {
            int x = 12;
            for (int y = 0; y < 348; ++y) {
                     screen_bound::write_pixel(x, y,  colour::black);
                     screen_bound::write_pixel(720 - x, y,  colour::black);
                    x += 2;
            }
        }

        void run() {

            std::cout
                << bios::video_adapter_names[bios::detect_video_adapter_type()] << " "
                <<  mode_names[ detect_mode()] << '\n'
                << "\ntest Hercules...\n";

            uint32_t time = 0;
            jtl::data_vector<size_type> v;

            // read the light pen registers
            /* {
                std::cout
                    << "\nPen regs = "
                    <<  read_light_pen_registers() << '\n';
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
                 graphics_mode();
                 cls();
            }
            // test write_pixel and time filling screen with every other pixel
            {
                bios::set_system_clock_counter(0);
                cross_hairs();
                time = bios::read_system_clock_counter();
                //fill_screen();
                time = bios::read_system_clock_counter() - time;
                //black_diagonals();
                std::getchar();
            }
            // test plot pixels from array of dword points
            {
                 cls();
                uint32_t data[16];
                gfx::union_point_t point;
                int x = 0;
                for (int y = 0; y < 16; ++y) { // build multi-point data array
                    point.coord.y = 100 + y;
                    point.coord.x = 100 - x;
                    x += 2;
                    data[y] = point.dword;
                     screen_bound::plot_point(point.dword);
                }
                // screen_bound::plot_multi_point(data, 16);
                std::getchar();
            }
            //swap buffers
            {
                uint32_t data[16];
                gfx::union_point_t point;
                int x = 0;
                for (int y = 0; y < 16; ++y) { // build multi-point data array
                    point.coord.y = 100 + y;
                    point.coord.x = 100 + x;
                    x += 2;
                    data[y] = point.dword;
                }
                 cls(0);
                 cls(1);
                 screen_bound::plot_multi_point(data, 16, 1);
                 swap_buffers();
                std::getchar();
                 screen_bound::unplot_multi_point(data, 16, 1);
                 swap_buffers();
            }
            // is_plot_point
            {
                 cls(0);
                cross_hairs(); // y = 360 x = 174
                gfx::union_point_t point(0, 0);
                assert(! screen_bound::is_plot_point(point.dword));
                 screen_bound::plot_point(point.dword);
                assert( screen_bound::is_plot_point(point.dword));
                point.coord.x = 360;
                for (int y = 0; y < 348; ++y) {
                    point.coord.y = y;
                    assert( screen_bound::is_plot_point(point.dword));
                    //if ( screen_bound::is_plot_point(point.dword)) {
                        // screen_bound::unplot_point(point.dword);
                    //}
                }
                point.coord.y = 174;
                for (int x = 0; x < 720; ++x) {
                    point.coord.x = x;
                    assert( screen_bound::is_plot_point(point.dword));
                    if ( screen_bound::is_plot_point(point.dword)) {
                         screen_bound::unplot_point(point.dword);
                    }
                }
                std::getchar();
            }
            // count plot point
            {
                gfx::point_vector_2d<8> donut("resource/donut.dat");
                donut.translate(360, 174);
                 cls();
                //fill_screen();
                 screen_bound::unplot_multi_point(donut.data(), donut.size());
                v.push_back( screen_bound::count_plot_multi_point(donut.data(), donut.size()));
                 screen_bound::plot_multi_point(donut.data(), donut.size());
                v.push_back( screen_bound::count_plot_multi_point(donut.data(), donut.size()));
                for (int i = 1; i <= 8; ++i) {
                     screen_bound::unplot_multi_point(donut.data(), i);
                    v.push_back( screen_bound::count_plot_multi_point(donut.data(), donut.size()));
                }
                std::getchar();
            }
            //relative
            {
                const jtl::size_t moore_neighbours[16] = {
                    -1, -1,
                     0, -1,
                     1, -1,
                    -1,  0,
                     1,  0,
                    -1,  1,
                     0,  1,
                     1,  1
                };

                const uint32_t moore[8] = {
                    0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001, 0x0000FFFF,
                    0x00000001, 0x0001FFFF, 0x00010000, 0x00010001
                };

                gfx::point_vector_2d<8> donut("resource/donut.dat");
                donut.translate(360, 174);
                gfx::point_vector_2d<8>neighbours;
                neighbours.add(moore_neighbours, 16);
                gfx::union_point_t p(361, 175);
                 cls();
                fill_screen();
                 screen_bound::unplot_multi_point(donut.data(), donut.size());
                //v.push_back( screen_bound::count_relative_plot_multi_point(p.dword, neighbours.data(), neighbours.size()));
                v.push_back( screen_bound::count_relative_plot_multi_point(p.dword, moore, 8));
                 screen_bound::plot_multi_point(donut.data(), donut.size());
                //v.push_back( screen_bound::count_relative_plot_multi_point(p.dword, neighbours.data(), neighbours.size()));
                v.push_back( screen_bound::count_relative_plot_multi_point(p.dword, moore, 8));
                for (int i = 1; i <= 8; ++i) {
                     screen_bound::unplot_multi_point(donut.data(), i);
                    //v.push_back( screen_bound::count_relative_plot_multi_point(p.dword, neighbours.data(), neighbours.size()));
                    v.push_back( screen_bound::count_relative_plot_multi_point(p.dword, moore, 8));
                }
                std::getchar();
            //}
            // return to text mode
            //{
                 text_mode();
                std::cout << std::dec << "time = " << time << '\n';
                std::cout << "count = " << v << '\n';
                std::cout << std::hex << "donut = " << donut << '\n';
                std::cout << "neighbours = " << neighbours << '\n';
                for (int i = 0; i < neighbours.size(); ++i) {
                    std::cout << neighbours.data()[i] << ' ';
                }
                std::cout << '\n';
                perror("error:");

            }

            std::cout << "success!\n";

        }

}

#endif