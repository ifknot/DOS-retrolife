/*
#include <iostream>
#include <stdint.h>
#include <vector>
#include <stdio.h>

//#include "retrolib/dos/dos_segmented_memory_block.h"
#include "retrolib/gfx/hga/test_hga.h"
//#include "retrolib/file/test_file_utilities.h"
//#include "retrolib/file/test_file_streams.h"
//#include "retrolib/memory/test_array.h"
//#include "retrolib/memory/test_data_vector.h"
//#include "retrolib/gfx/test_point_vector_2d.h"
//#include "retrolib/memory/test_memory_unions.h"
//#include "retrolib/automata/test_count_neighbours.h"

int main() {

    test_hga::run();

}
*/

#include <iostream>

#include "retrolib/gfx/hga/hga_graphics.h"

int main() {
    
    hga::graphics_mode();
    hga::select_buffer(0);
    hga::cls(0);
    
}
/*
#include <cassert>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "retrolib/bios/bios_clock_services.h"
#include "retrolib/gfx/hga/hga_graphics.h"
#include "retrolib/gfx/point_2d.h"
#include "retrolib/gfx/point_vector_2d.h"

int main(int argc, char* argv[]) {

    std::vector<std::string> arg_list(argv, argv + argc);
   
    for (int i = 0; i < arg_list.size(); ++i) {
        std::cout << arg_list[i].c_str() << '\n';
    }

    assert(argc > 4);

    uint32_t cycles, sum, time = 0;
    jtl::union_point_t p;
    

    uint16_t w, h, ox, oy;
    cycles = atoi(arg_list[1].c_str());
    h = atoi(arg_list[2].c_str()); //40; // SCREEN_Y_MAX;
    w = atoi(arg_list[3].c_str()); //40; // SCREEN_X_MAX;
    oy = (SCREEN_Y_MAX / 2) - (h / 2);
    ox = (SCREEN_X_MAX / 2) - (w / 2);
    char vis = 0;
    char hid = 1;

    std::cout << "Conway's Game of Life " << w << 'x' << h << " - Press Enter\n";
    int c = getchar();
    if (c == 'q') return 1;

    const uint32_t moore[8] = {
        0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001, 0x0000FFFF,
        0x00000001, 0x0001FFFF, 0x00010000, 0x00010001
    };
  
    hga::graphics_mode();
    hga::cls();

    jtl::point_vector_2d<8> r0(arg_list[4].c_str());
    r0.translate(ox, oy);
    hga::screen_bound::plot_multi_point(r0.data(), r0.size(), vis);
    if (argc > 5) {
        jtl::point_vector_2d<8> r1(arg_list[5].c_str());
        r1.translate(ox + 10, oy + 10);
        hga::screen_bound::plot_multi_point(r1.data(), r1.size(), vis);
    }
    if (argc > 6) {
        jtl::point_vector_2d<8> r2(arg_list[6].c_str());
        r2.translate(ox + 20, oy + 20);
        hga::screen_bound::plot_multi_point(r2.data(), r2.size(), vis);
    }
   
    time = bios::read_system_clock_counter();
    for(int i = 0; i < cycles; ++i) {
        hga::cls(hid);
        for (uint16_t y = 0; y < h; ++y) {
            for (uint16_t x = 0; x < w; ++x) {
                p.coord.x = ox + x;
                p.coord.y = oy + y;
                sum = hga::screen_bound::count_relative_plot_multi_point(p.dword, moore, 8, vis);
                if(hga::screen_bound::is_plot_point(p.dword, vis) && (sum == 2 || sum == 3)) {
                    hga::screen_bound::plot_point(p.dword, hid);
                }
                else if (sum == 3) {
                    hga::screen_bound::plot_point(p.dword, hid);
                }
            }
            if (y & 1) {
                p.coord.x = ox - 2;
                hga::screen_bound::plot_point(p.dword, vis);
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
    std::cout << "time = " << (float)time / 18.2 << " seconds\n";

}
*/