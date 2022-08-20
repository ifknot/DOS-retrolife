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

#include "../retrolib/gfx/mda/mode7/mda_mode7.h"
#include "../retrolib/gfx/mda/mode7/mda_mode7_write_character.h"

#include "../retrolib/memory/size_t.h"

using namespace bios;
using namespace mda::mode7;
using namespace jtl;

namespace game {

	jtl::union_point_t player(8, 8);

	static const char TILE = 0xC5;
	static const char PLAYER = 0x01;

	static const jtl::size_t NEIGHBOURHOOD_SIZE = 18;
	static const int8_t NEIGHBOURHOOD[NEIGHBOURHOOD_SIZE] = { 0, 0, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1, 0, -1, 1, -1 };

	template<jtl::size_t POW2_POLICY = 4>
	class maze_t {

		static const char NUL = 0;


	public:

		typedef jtl::size_t size_type;
		typedef int8_t value_type;

		maze_t() :
			width_(1 << POW2_POLICY),
			height_(width_),
			size_(width_* height_),
			visisble_data_(new value_type[size_]),
			hidden_data_(new value_type[size_])
		{
			build_maze();
		}

		~maze_t() {
			delete[] visisble_data_;
			delete[] hidden_data_;
		}

		
		value_type operator()(size_type x, size_type y) const {
			if (x >= 0 && x < width_ && y >= 0 && y < height_) {
				return visisble_data_[(y << POW2_POLICY) + x];
			}
			return NUL;
		}

		inline const value_type* data() const {
			return visisble_data_;
		}

		template<jtl::size_t T>
		void draw(jtl::size_t x, jtl::size_t y, maze_t<T> maze) {
			for (jtl::size_t j = 0; j < maze.height(); ++j) {
				for (jtl::size_t i = 0; i < maze.width(); ++i) {
					screen_bound::write_character(x + i, y + j, maze(i, j));
				}
			}
			screen_bound::write_character(x + player.coord.x, y + player.coord.y, PLAYER);
		}

		inline size_type height() const {
			return height_;
		}

		void hide(size_type x, size_type y) {
			if (x >= 0 && x < width_ && y >= 0 && y < height_) {
				visisble_data_[(y << POW2_POLICY) + x] = NUL;
			}
		}

		void hide_all() {
			for (size_type i = 0; i < size_; ++i) {
				visisble_data_[i] = NUL;
			}
		}

		void reveal(size_type x, size_type y) {
			if (x >= 0 && x < width_ && y >= 0 && y < height_) {
				size_type i = (y << POW2_POLICY) + x;
				visisble_data_[i] = hidden_data_[i];
			}
		}

		void reveal_all() {
			for (size_type i = 0; i < size_; ++i) {
				visisble_data_[i] = hidden_data_[i];
			}
		}

		void reveal_neighbours(size_type x, size_type y) {
			for (size_type i = 0; i < NEIGHBOURHOOD_SIZE; i += 2) {
				reveal(x + NEIGHBOURHOOD[i], y + NEIGHBOURHOOD[i + 1]);
			}
		}

		inline size_type size() const {
			return size_;
		}

		inline size_type width() const {
			return width_;
		}

	private:

		void build_maze() {
			hide_all();
			for (size_type i = 0; i < size_; ++i) {
				hidden_data_[i] = TILE;
			}
		}

		size_type width_, height_, size_;
		value_type* visisble_data_;
		value_type* hidden_data_;

	};

	

}

	namespace test_maze {

		typedef game::maze_t<> maze16x16_t;

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
				//player* p = new player();
				//m.add(p);
				//m.add(new monster());
				uint8_t k = 0;
				while (k != 'q') {
					//m.reveal_neighbours(p.x(), p.y());
					m.reveal_neighbours(game::player.coord.x, game::player.coord.y);
					m.draw(52, 4, m);
					//m.key(wait_key_scan_code());
					k = wait_key_ascii();
					switch (k) {
					case 'w':
						--game::player.coord.y;
						break;
					case 's':
						++game::player.coord.y;
						break;
					case 'd':
						++game::player.coord.x;
						break;
					case 'a':
						--game::player.coord.x;
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
