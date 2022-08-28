/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.08.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MAZE_OBJECT_H
#define MAZE_OBJECT_H

#include "../retrolib/gfx/point_2d.h"

#include "maze.h"

namespace game {

	template<jtl::size_t T>
	class maze_object {

	public:

		maze_object(maze_t<T>& maze, jtl::size_t x, jtl::size_t y, char chr) :
			maze(maze),
			p(x, y),
			chr(chr),
			old_chr(FLOOR)
		{
			maze(x, y, chr);		
		}

		void move(jtl::size_t x, jtl::size_t y) {
			if (x < maze.width() && y < maze.height()) {
				switch (maze(x, y)) {
				case FLOOR:
					maze(p.coord.x, p.coord.y, old_chr);
					old_chr = maze(x, y);
					maze(x, y, chr);
					p.move(x, y);
					break;
				default:
					break;
				}
				
			}
		}

		inline void move_north() {
			move(p.coord.x, p.coord.y - 1);
		}

		inline void move_south() {
			move(p.coord.x, p.coord.y + 1);
		}

		inline void move_east() {
			move(p.coord.x - 1, p.coord.y);
		}

		inline void move_west() {
			move(p.coord.x + 1, p.coord.y);
		}

		inline gfx::union_point_t position() {
			return p;
		}

	private:

		maze_t<T>& maze;
		gfx::union_point_t p;
		char chr, old_chr;

	};

}

#endif