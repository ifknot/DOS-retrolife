
#include <iostream>
#include <stdint.h>
#include <vector>
#include <stdio.h>

//#include "retrolib/dos/dos_segmented_memory_block.h"
//#include "retrolib/gfx/hga/test_hga.h"
//#include "retrolib/file/test_file_utilities.h"
//#include "retrolib/file/test_file_streams.h"
//#include "retrolib/memory/test_array.h"
//#include "retrolib/memory/test_data_vector.h"
//#include "retrolib/gfx/test_point_vector_2d.h"
//#include "retrolib/memory/test_memory_unions.h"
//#include "retrolib/automata/test_count_neighbours.h"

#include "retrolib/bios/bios_clock_services.h"
#include "retrolib/gfx/hga/hga_graphics.h"
#include "retrolib/gfx/point_2d.h"
#include "retrolib/gfx/point_vector_2d.h"

int main() {

    const uint32_t moore[8] = {
        0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001, 0x0000FFFF,
        0x00000001, 0x0001FFFF, 0x00010000, 0x00010001
    };

    uint32_t time, sum;
    time = sum = 0;
    jtl::union_point_t p;
    
    hga::graphics_mode();
    hga::cls();
    time = bios::read_system_clock_counter();
    uint16_t w, h, ox, oy;
    h = 40; // SCREEN_Y_MAX;
    w = 40; // SCREEN_X_MAX;
    oy = (SCREEN_Y_MAX / 2) - (h / 2);
    ox = (SCREEN_X_MAX / 2) - (w / 2);
    char buf = 0;
    char hid = 1;
    jtl::point_vector_2d<8> glider("resource/glider.dat");
    glider.translate(ox + 10, oy + 10);
    hga::screen_bound::plot_multi_point(glider.data(), glider.size(), buf);
    jtl::point_vector_2d<8> glider2("resource/glider2.dat");
    glider2.translate(ox , oy);
    hga::screen_bound::plot_multi_point(glider2.data(), glider2.size(), buf);

    for(int i = 0; i < 150; ++i) {
        hga::cls(hid);
        for (uint16_t y = 0; y < h; ++y) {
            for (uint16_t x = 0; x < w; ++x) {
                p.coord.x = ox + x;
                p.coord.y = oy + y;
                sum = hga::screen_bound::count_relative_plot_multi_point(p.dword, moore, 8, buf);
                if(hga::screen_bound::is_plot_point(p.dword, buf) && (sum == 2 || sum == 3)) {
                    hga::screen_bound::plot_point(p.dword, hid);
                }
                else if (sum == 3) {
                    hga::screen_bound::plot_point(p.dword, hid);
                }
            }
            //if (y & 1) {
                //p.coord.x = ox - 2;
                //hga::screen_bound::plot_point(p.dword, buf);
            //}
        }      
        //hga::swap_buffers();
        buf = hid;
        hid ^= 1;
        hga::select_buffer(buf);
    }
    time = bios::read_system_clock_counter() - time;
    
    getchar();
    hga::text_mode();
    std::cout << "sum = " << sum << "\n";
    std::cout << "time = " << (float)time / 18.2 << " seconds\n";

}
