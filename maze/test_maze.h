/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      20.08.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_MAZE_H
#define TEST_MAZE_H

#include "../retrolib/bios/bios_services.h"

#include "../retrolib/gfx/point_2d.h"
#include "../retrolib/gfx/dimension_2d.h"

#include "../retrolib/gfx/mda/mode7/mda_mode7.h"
#include "../retrolib/gfx/mda/mode7/mda_mode7_write_character.h"

#include "../retrolib/memory/size_t.h"

#include "maze.h"
#include "maze_object.h"

using namespace bios;
using namespace mda::mode7;
using namespace jtl;

namespace game {

	static const jtl::size_t SCALE = 5;

	typedef maze_t<SCALE> maze16x16_t;

	gfx::union_point_t screen_map_p(52, 4);
	gfx::union_dimension_t screen_map_d(16, 16);

	// the maze locations relative to the player's location that can be shown on the screen map
	static const jtl::size_t maze_x_coords[16] = { -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7 };
	static const jtl::size_t maze_y_coords[16] = { -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7 };

	static const jtl::size_t NEIGHBOURHOOD_SIZE = 18;
	// using 18 x,y coords instead of 3 x and 3 y arrays allows any shape of visible neighbourhood 
	static const jtl::size_t NEIGHBOURHOOD[NEIGHBOURHOOD_SIZE] = { 0, 0, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1, 0, -1, 1, -1 };

	template<jtl::size_t T>
	void draw_visible_map(maze_t<T>& maze, jtl::size_t ox, jtl::size_t oy, jtl::size_t x, jtl::size_t y) {
		for (jtl::size_t j = 0; j < screen_map_d.dim.height; ++j) {
			for (jtl::size_t i = 0; i < screen_map_d.dim.width; ++i) {
				screen_bound::write_character(
					x + i, 
					y + j, 
					maze(
						ox + maze_x_coords[i], 
						oy + maze_y_coords[j]
					)
				);
			}
		}
	}

	void run() {
		std::cout
			<< "Using video card "
			<< video_adapter_names[detect_video_adapter_type()] << "\n Mode "
			<< video_mode_names[get_video_state().mode] << "\n"
			<< "Switch to mode 7 and ENTER the maze...\n";
		wait_key_ascii();
		enter();
		{
			maze16x16_t m;
			maze_object<SCALE> player(m, m.width() / 2, m.height() / 2, 0x03);

			//build_maze(m);
			
			uint8_t k = 0;
			while (k != 'q') {
				m.reveal_neighbours(player.position().coord.x, player.position().coord.y);
				draw_visible_map(m, player.position().coord.x, player.position().coord.y, screen_map_p.coord.x, screen_map_p.coord.y);
				//m.key(wait_key_scan_code());
				k = wait_key_ascii();
				switch (k) {
				case 'w':
					player.move_north();
					break;
				case 's':
					player.move_south();
					break;
				case 'd':
					player.move_west();
					break;
				case 'a':
					player.move_east();;
					break;
				}
			}
		}

		std::cout
			<< "\n Mode "
			<< video_mode_names[get_video_state().mode] << "\n"
			<< "Switch back and EXIT the maze...\n";
		wait_key_ascii();
		exit();
		std::cout << "mode " << bios::video_mode_names[get_video_state().mode] << "\n";
		std::cout << "success!\n";
	}

}

#endif
