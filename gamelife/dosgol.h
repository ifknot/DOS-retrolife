/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef DOSGOL_H
#define DOSGOL_H

#include <cassert>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "retrolib/bios/bios_clock_services.h"
#include "retrolib/gfx/hga/hga_graphics.h"
#include "retrolib/gfx/point_2d.h"
#include "retrolib/gfx/point_vector_2d.h"

namespace dosgol {

    int run(int argc, char* argv[]) {

        for (int i = 0; i < argc; ++i) {
            std::cout << argv[i] << '\n';
        }

        assert(argc > 4);

        uint32_t gen, sum, time = 0;

        uint16_t w, h, ox, oy;
        gen = atoi(argv[1]);
        h = atoi(argv[2]); //40; // SCREEN_Y_MAX;
        w = atoi(argv[3]); //40; // SCREEN_X_MAX;
        oy = (SCREEN_Y_MAX / 2) - (h / 2);
        ox = (SCREEN_X_MAX / 2) - (w / 2);
        char vis = 0;
        char hid = 1;
        jtl::union_point_t p, q(ox - 2, oy);

        std::cout << "Conway's Game of Life " << w << 'x' << h << " - Press Enter\n";
        int c = getchar();
        if (c == 'q') {
            return 1;
        }

        const uint32_t moore[8] = {
            0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001, 0x0000FFFF,
            0x00000001, 0x0001FFFF, 0x00010000, 0x00010001
        };

        hga::graphics_mode();
        hga::cls();

        jtl::point_vector_2d<8> r0(argv[4]);
        r0.translate(ox, oy);
        hga::screen_bound::plot_multi_point(r0.data(), r0.size(), vis);
        if (argc > 5) {
            jtl::point_vector_2d<8> r1(argv[5]);
            r1.translate(ox + 10, oy + 10);
            hga::screen_bound::plot_multi_point(r1.data(), r1.size(), vis);
        }
        if (argc > 6) {
            jtl::point_vector_2d<8> r2(argv[6]);
            r2.translate(ox + 20, oy + 20);
            hga::screen_bound::plot_multi_point(r2.data(), r2.size(), vis);
        }

        time = bios::read_system_clock_counter();
        for (int i = 0; i < gen; ++i) {
            hga::cls(hid);
            for (uint16_t y = 0; y < h; ++y) {
                for (uint16_t x = 0; x < w; ++x) {
                    p.coord.x = ox + x;
                    p.coord.y = oy + y;
                    sum = hga::screen_bound::count_relative_plot_multi_point(p.dword, moore, 8, vis);
                    if (hga::screen_bound::is_plot_point(p.dword, vis) && (sum == 2 || sum == 3)) {
                        hga::screen_bound::plot_point(p.dword, hid);
                    }
                    else if (sum == 3) {
                        hga::screen_bound::plot_point(p.dword, hid);
                    }
                }
                if (y & 1) {
                    hga::screen_bound::unplot_point(q.dword, vis);
                    q.coord.y = oy + y;
                    hga::screen_bound::plot_point(q.dword, vis);
                }
            }
            //hga::swap_buffers();
            vis = hid;
            hid ^= 1;
            hga::select_buffer(vis);
        }
        time = bios::read_system_clock_counter() - time;

        hga::select_buffer(0);
        getchar();
        hga::text_mode();
        std::cout << "time " << gen << " generations = " << (float)time / 18.2 << " seconds\n";

        return 0;
    }

}

#endif