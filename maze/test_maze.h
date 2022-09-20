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

#include <iostream>

#include "../retrolib/bios/bios_services.h"

#include "../retrolib/gfx/gfx_point_2d.h"
#include "../retrolib/gfx/gfx_dimension_2d.h"

#include "../retrolib/gfx/mda/mode7/mda_mode7.h"
#include "../retrolib/gfx/mda/mode7/mda_mode7_write_character.h"
#include "../retrolib/gfx/mda/mode7/mda_mode7_fill_area.h"
#include "../retrolib/gfx/mda/mode7/mda_mode7_write_bitmap.h"

#include "../retrolib/memory/size_t.h"

#include "maze.h"
#include "maze_player.h"
#include "maze_draw_wall.h"
#include "maze_bitmaps.h"

using namespace bios;
using namespace mda::mode7;

namespace game {

	static const mda::size_type SCALE = 4;

	typedef maze_t<SCALE> maze16x16_t;

	gfx::union_point_t screen_map_p(58, 4);
	gfx::union_point_t screen_walls(0, 0);
	gfx::union_dimension_t screen_map_d(16, 16);

	// the maze locations relative to the player's location that can be shown on the screen map
	static const mda::size_type map_x_coords[16] = { -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7 };
	static const mda::size_type map_y_coords[16] = { -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7 };

	static const mda::size_type neighbour_count = 18;
	// using 18 x,y coords instead of 3 x and 3 y arrays allows any shape of visible neighbourhood 
	static const mda::size_type neighbourhood[18] = { 0, 0, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1, 0, -1, 1, -1 };

	// screen x offsets for left and right walls and their common screen y offsets
	static const mda::size_type left_wall_x[7] =	{  0,  1,  9, 15, 19, 22, 24 };
	static const mda::size_type right_wall_x[7] =	{ 50, 49, 41, 35, 31, 28, 26 };
	static const mda::size_type wall_y[7] =			{  1,  1,  5,  8, 10, 12, 12};

	template<mda::size_type T>
	void draw_map(maze_t<T>& maze, mda::size_type ox, mda::size_type oy, mda::size_type x, mda::size_type y) {
		for (mda::size_type j = 0; j < screen_map_d.dim.height; ++j) {
			for (mda::size_type i = 0; i < screen_map_d.dim.width; ++i) {
				screen_bound::write_character(
					x + i, 
					y + j, 
					maze(
						ox + map_x_coords[i], 
						oy + map_y_coords[j]
					)
				);
			}
		}
	}


	template<mda::size_type T>
	void draw_walls(maze_t<T>& maze, mda::size_type ox, mda::size_type oy, mda::size_type x, mda::size_type y) {
		for (uint8_t i = 0; i < 7; ++i) {
			// replace with draw_bitmap(x,y,bmp[i][distance])
			draw_wall_left(x + left_wall_x[i], y + wall_y[i], i); 
			draw_wall_right(x + right_wall_x[i], y + wall_y[i], i);
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

			screen_bound::fill_area_attribute(0, 0, 50, 50, attribute::reverse);

			maze16x16_t m;
			assert(m.load("maze/test.dat"));
			maze_player<SCALE> player(m, m.width() / 2, m.height() / 2);
			
			
			uint8_t k = 0;
			m.reveal_neighbours(player.position().coord.x, player.position().coord.y);
			draw_map(m, player.position().coord.x, player.position().coord.y, screen_map_p.coord.x, screen_map_p.coord.y);
	
			//draw_walls(m, player.position().coord.x, player.position().coord.y, screen_walls.coord.x, screen_walls.coord.y);
			gfx::bitmap lw0(1, 25, COLOUR_DEPTH, bios::TEXT_MONOCHROME_80X25, left_wall_0);
			screen_bound::write_bitmap(0, 0, &lw0);
			gfx::bitmap rw0(1, 25, COLOUR_DEPTH, bios::TEXT_MONOCHROME_80X25, right_wall_0);
			screen_bound::write_bitmap(50, 0, &rw0);

			gfx::bitmap lw1(8, 23, COLOUR_DEPTH, bios::TEXT_MONOCHROME_80X25, left_wall_1);
			screen_bound::write_bitmap(1, 1, &lw1);
			gfx::bitmap rw1(8, 23, COLOUR_DEPTH, bios::TEXT_MONOCHROME_80X25, right_wall_1);
			screen_bound::write_bitmap(42, 1, &rw1);
			
			gfx::bitmap lw2(6, 15, COLOUR_DEPTH, bios::TEXT_MONOCHROME_80X25, left_wall_2);
			screen_bound::write_bitmap(9, 5, &lw2);
			gfx::bitmap rw2(6, 15, COLOUR_DEPTH, bios::TEXT_MONOCHROME_80X25, right_wall_2);
			screen_bound::write_bitmap(36, 5, &rw2);

			gfx::bitmap lw3(4, 9, COLOUR_DEPTH, bios::TEXT_MONOCHROME_80X25, left_wall_3);
			screen_bound::write_bitmap(15, 8, &lw3);
			gfx::bitmap rw3(4, 9, COLOUR_DEPTH, bios::TEXT_MONOCHROME_80X25, right_wall_3);
			screen_bound::write_bitmap(32, 8, &rw3);

			while (m.is_locked()) {
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
					player.move_east();
					break;
				case 'q':
					m.unlock();
					break;
				}
				m.reveal_neighbours(player.position().coord.x, player.position().coord.y);
				draw_map(m, player.position().coord.x, player.position().coord.y, screen_map_p.coord.x, screen_map_p.coord.y);
				
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
