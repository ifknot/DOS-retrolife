/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.08.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MAZE_PLAYER_H
#define MAZE_PLAYER_H

#include "../retrolib/gfx/gfx_point_2d.h"

#include "maze.h"

namespace game {

	static char player_glyph[4] = { 0x18, 0x19, 0x1A, 0x1B };

	template<jtl::size_t T>
	class maze_player {

	public:

		maze_player(maze_t<T>& maze, jtl::size_t x, jtl::size_t y) :
			maze(maze),
			p(x, y),
			chr(FLOOR),
			direction_(north)
		{
			maze(x, y, player_glyph[direction_]);
		}

		inline jtl::size_t direction() {
			return direction_;
		}

		void move(jtl::size_t x, jtl::size_t y) {
			if (x < maze.width() && y < maze.height()) {
				switch (maze(x, y)) {
				case FLOOR:
					raw_move(x, y);
					break;
				case EXIT:
					raw_move(x, y);
					maze.unlock();
					break;
				default:
					break;
				}
				
			}
		}

		inline void move_north() {
			if (direction_ == north) {
				move(p.coord.x, p.coord.y - 1);
			}
			else {
				direction_ = north;
				maze(p.coord.x, p.coord.y, player_glyph[direction_]);
			}
		}

		inline void move_south() {
			if (direction_ == south) {
				move(p.coord.x, p.coord.y + 1);
			}
			else {
				direction_ = south;
				maze(p.coord.x, p.coord.y, player_glyph[direction_]);
			}
		}

		inline void move_east() {
			if (direction_ == east) {
				move(p.coord.x - 1, p.coord.y);
			}
			else {
				direction_ = east;
				maze(p.coord.x, p.coord.y, player_glyph[direction_]);
			}
		}

		inline void move_west() {
			if (direction_ == west) {
				move(p.coord.x + 1, p.coord.y);
			}
			else {
				direction_ = west;
				maze(p.coord.x, p.coord.y, player_glyph[direction_]);
			}
		}

		inline gfx::union_point_t position() {
			return p;
		}

	private:

		inline void raw_move(jtl::size_t x, jtl::size_t y) {
			maze(p.coord.x, p.coord.y, chr);
			chr = maze(x, y);
			maze(x, y, player_glyph[direction_]);
			p.move(x, y);
		}

		maze_t<T>& maze;
		gfx::union_point_t p;
		char chr;
		direction_t direction_;

	};

}

#endif