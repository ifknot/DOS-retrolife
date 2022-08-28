/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.08.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MAZE_ITEMS_H
#define MAZE_ITEMS_H

namespace game {

	enum direction_t { north, south, west, east };

	static char direction_glyph[4] = { 0x18, 0x19, 0x1A, 0x1B };

	static const char FLOOR = 0xF9;
	static const char WALL = 0xDB;
	static const char EXIT = 0x58;
	static const char PLAYER = 0x01;

}

#endif