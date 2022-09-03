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
#include "maze_draw_wall.h"

using namespace bios;
using namespace mda::mode7;

namespace game {

	static const mda::size_type SCALE = 4;

	typedef maze_t<SCALE> maze16x16_t;

	gfx::union_point_t screen_map_p(52, 4);
	gfx::union_dimension_t screen_map_d(16, 16);

	// the maze locations relative to the player's location that can be shown on the screen map
	static const mda::size_type map_x_coords[16] = { -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7 };
	static const mda::size_type map_y_coords[16] = { -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7 };

	static const mda::size_type NEIGHBOURHOOD_SIZE = 18;
	// using 18 x,y coords instead of 3 x and 3 y arrays allows any shape of visible neighbourhood 
	static const mda::size_type NEIGHBOURHOOD[NEIGHBOURHOOD_SIZE] = { 0, 0, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1, 0, -1, 1, -1 };

	static const mda::size_type face_x[4] = {  0,  0,  1, -1 };
	static const mda::size_type face_y[4] = { -1,  1,  0,  0 };
	static const mda::size_type left_x[4] = { -1,  1,  0,  0 };
	static const mda::size_type left_y[4] = {  0,  0, -1,  1 };
	static const mda::size_type right_x[4] = { 1, -1,  0,  0 };
	static const mda::size_type right_y[4] = { 0,  0,  1, -1 };

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

	void draw_left_wall(mda::size_type s, mda::size_type x, mda::size_type y) {}

	void draw_right_wall(mda::size_type s, mda::size_type x, mda::size_type y) {}

	static const mda::size_type face_i[5] = { 7, 5, 3, 3, 1 };
	static const mda::size_type face_j[5] = { 9, 7, 5, 3, 1 };
	static const mda::size_type face_x_off[5] = { 2, 3, 4, 5, 6 }; 
	static const mda::size_type face_y_off[5] = { 3, 4, 5, 5, 6 };

	void draw_face_wall(mda::size_type s, mda::size_type x, mda::size_type y) {
		x += face_x_off[s];
		y += face_y_off[s];
		for (mda::size_type i = 0; i < face_i[s]; ++i) {
			for (mda::size_type j = 0; j < face_j[s]; ++j) {
				screen_bound::write_character(x + j, y + i, FACE_LIGHT);
			}
		}
	}

	template<mda::size_type T>
	void draw_walls(maze_t<T>& maze, mda::size_type d, mda::size_type ox, mda::size_type oy, mda::size_type x, mda::size_type y) {
		for (mda::size_type i = 0; i < 10; ++i) {
			for (mda::size_type j = 0; j < 13; ++j) {
				screen_bound::write_character(x + j, y + i, ' ');
			}
		}
		for (mda::size_type i = 0; i < 5; ++i) {
			if (maze(ox + left_x[d], oy + left_y[d]) == WALL) {
				draw_left_wall(i, x, y);
			}
			else {
				//draw_left_face(i, x, y);
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
			//draw_walls(m, player.direction(), player.position().coord.x, player.position().coord.y, 0, 0);
			
			draw_wall_left(0, 1, 0);
			draw_wall_left(1, 1, 1);
			draw_wall_left(9, 5, 2);
			draw_wall_left(15, 8, 3);
			draw_wall_left(19, 10, 4);
			draw_wall_left(22, 12, 5);
			draw_wall_left(24, 12, 6);
			
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
				//draw_walls(m, player.direction(), player.position().coord.x, player.position().coord.y, 0, 0);
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
