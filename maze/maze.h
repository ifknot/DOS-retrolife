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

	static const char FLOOR = 0xF9;
	static const char WALL = 0xDB;
	static const char PLAYER = 0x01;

	template<jtl::size_t POW2_POLICY>
	class maze_t {

		static const char NUL = 0;	

	public:

		enum state_t { hidden, visible };

		struct element_t {

			uint8_t chr, state;

		};

		union union_element_t {

			uint16_t word;
			element_t tile;

			union_element_t() : word(0x00F9) {}

		};

		typedef jtl::size_t size_type;
		typedef union_element_t value_type;

		maze_t() :
			width_(1 << POW2_POLICY),
			height_(width_),
			size_(width_* height_),
			data_(new value_type[size_])
		{}

		~maze_t() {
			delete[] data_;
		}


		char operator()(size_type x, size_type y) const {
			if (x < width_ && y < height_) {
				return (data_[(y << POW2_POLICY) + x].tile.state & visible)
					? data_[(y << POW2_POLICY) + x].tile.chr
					: NUL;
			}
			return NUL;
		}

		void operator()(size_type x, size_type y, char c) {
			if (x < width_ && y < height_) {
				data_[(y << POW2_POLICY) + x].tile.chr = c;
			}
		}

		inline const value_type* data() const {
			return data_;
		}

		inline size_type height() const {
			return height_;
		}

		void hide(size_type x, size_type y) {
			if (x < width_ && y < height_) {
				data_[(y << POW2_POLICY) + x].tile.state = hidden;
			}
		}

		void hide_all() {
			for (size_type i = 0; i < size_; ++i) {
				data_[i].tile.sate = hidden;
			}
		}

		inline bool is_floor(size_type x, size_type y) {
			if (x < width_ && y < height_) {
				return data_[(y << POW2_POLICY) + x].tile.chr == FLOOR;
			}
			return false;
		}

		void reveal(size_type x, size_type y) {
			if (x < width_ && y < height_) {
				data_[(y<< POW2_POLICY) + x].tile.state = visible;
			}
		}

		void reveal_all() {
			for (size_type i = 0; i < size_; ++i) {
				data_[(y << POW2_POLICY) + x]..tile.state = visible;
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

		size_type width_, height_, size_;
		value_type* data_;

	};

}

#endif