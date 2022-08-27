/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      27.08.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MAZE_H
#define MAZE_H

#include "../retrolib/memory/size_t.h"

namespace game {

	static const char TILE = 0xC5;
	static const char PLAYER = 0x01;

	static const jtl::size_t NEIGHBOURHOOD_SIZE = 18;
	// using 18 x,y coords instead of 3 x and 3 y arrays allows any shape of visible neighbourhood 
	static const jtl::size_t NEIGHBOURHOOD[NEIGHBOURHOOD_SIZE] = { 0, 0, 1, 0, 1, 1, 0, 1, -1, 1, -1, 0, -1, -1, 0, -1, 1, -1 };

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
			if (x < width_ && y < height_) {
				return visisble_data_[(y << POW2_POLICY) + x];
			}
			return NUL;
		}

		inline const value_type* data() const {
			return visisble_data_;
		}

		inline size_type height() const {
			return height_;
		}

		void hide(size_type x, size_type y) {
			if (x < width_ && y < height_) {
				visisble_data_[(y << POW2_POLICY) + x] = NUL;
			}
		}

		void hide_all() {
			for (size_type i = 0; i < size_; ++i) {
				visisble_data_[i] = NUL;
			}
		}

		void reveal(size_type x, size_type y) {
			if (x < width_ && y < height_) {
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

#endif