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

#include "../retrolib/gfx/point_2d.h"
#include "../retrolib/gfx/dimension_2d.h"

#include "../retrolib/gfx/mda/mode7/mda_mode7.h"
#include "../retrolib/gfx/mda/mode7/mda_mode7_write_character.h"

#include "../retrolib/memory/size_t.h"

#include "maze.h"
#include "maze_player.h"

using namespace bios;
using namespace mda::mode7;
using namespace jtl;

namespace game {

	static const jtl::size_t SCALE = 4;

	typedef maze_t<SCALE> maze16x16_t;

	gfx::union_point_t screen_map_p(52, 4);
	gfx::union_dimension_t screen_map_d(16, 16);

	// the maze locations relative to the player's location that can be shown on the screen map
	static const jtl::size_t map_x_coords[16] = { -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7 };
	static const jtl::size_t map_y_coords[16] = { -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7 };

	static const jtl::size_t NEIGHBOURHOOD_SIZE = 18;
	// using 18 x,y coords instead of 3 x and 3 y arrays allows any shape of visible neighbourhood 
	static const jtl::size_t NEIGHBOURHOOD[NEIGHBOURHOOD_SIZE] = { 0, 0, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1, 0, -1, 1, -1 };

	static const jtl::size_t face_x[4] = {  0,  0,  1, -1 };
	static const jtl::size_t face_y[4] = { -1,  1,  0,  0 };
	//static const jtl::size_t left_x[4] = { -1,  1,  0,  0 };
	//static const jtl::size_t left_y[4] = {  0,  0, -1,  1 };
	//static const jtl::size_t right_x[4] = { 1, -1,  0,  0 };
	//static const jtl::size_t right_y[4] = { 0,  0,  1, -1 };

	template<jtl::size_t T>
	void draw_map(maze_t<T>& maze, jtl::size_t ox, jtl::size_t oy, jtl::size_t x, jtl::size_t y) {
		for (jtl::size_t j = 0; j < screen_map_d.dim.height; ++j) {
			for (jtl::size_t i = 0; i < screen_map_d.dim.width; ++i) {
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

	void draw_left_wall(jtl::size_t s, jtl::size_t x, jtl::size_t y) {}

	void draw_right_wall(jtl::size_t s, jtl::size_t x, jtl::size_t y) {}

	static const jtl::size_t face_i[5] = { 7, 5, 3, 3, 1 };
	static const jtl::size_t face_j[5] = { 9, 7, 5, 3, 1 };
	static const jtl::size_t face_x_off[5] = { 2, 3, 4, 5, 6 }; 
	static const jtl::size_t face_y_off[5] = { 3, 4, 5, 5, 6 };

	void draw_face_wall(jtl::size_t s, jtl::size_t x, jtl::size_t y) {
		std::cout << s << std::endl;
		x += face_x_off[s];
		y += face_y_off[s];
		for (jtl::size_t i = 0; i < face_i[s]; ++i) {
			for (jtl::size_t j = 0; j < face_j[s]; ++j) {
				screen_bound::write_character(x + j, y + i, FACE_LIGHT);
			}
		}
	}

	template<jtl::size_t T>
	void draw_walls(maze_t<T>& maze, jtl::size_t d, jtl::size_t ox, jtl::size_t oy, jtl::size_t x, jtl::size_t y) {
		for (jtl::size_t i = 0; i < 10; ++i) {
			for (jtl::size_t j = 0; j < 13; ++j) {
				screen_bound::write_character(x + j, y + i, ' ');
			}
		}
		for (jtl::size_t i = 0; i < 5; ++i) {
			if (maze(ox + left_x[d], oy + left_y[d]) == WALL) {
				draw_left_wall(i, x, y);
			}
			else {
				draw left face
			}
			//if (maze(ox + right_x[d], oy + right_y[d]) == WALL) draw_right_wall(i, x, y);
			//else draw right face
			ox += face_x[d];	// move fwd in the direction facing
			oy += face_y[d];
			if (maze.at(ox, oy) == WALL) {
				draw_face_wall(i, x, y);
				break;
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
			assert(m.load("maze/test.dat"));
			maze_player<SCALE> player(m, m.width() / 2, m.height() / 2);
			
			
			uint8_t k = 0;
			m.reveal_neighbours(player.position().coord.x, player.position().coord.y);
			draw_map(m, player.position().coord.x, player.position().coord.y, screen_map_p.coord.x, screen_map_p.coord.y);
			draw_walls(m, player.direction(), player.position().coord.x, player.position().coord.y, 0, 0);
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
				draw_walls(m, player.direction(), player.position().coord.x, player.position().coord.y, 0, 0);
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
