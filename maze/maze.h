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

#include <fstream>
#include <iostream>
#include <string>

#include "../retrolib/dos/dos_error_messages.h"

#include "../retrolib/memory/size_t.h"

#include "maze_items.h"

namespace game {

	template<jtl::size_t POW2_POLICY>
	class maze_t {

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
			data_(new value_type[size_]),
			locked_(true)
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

		char at(size_type x, size_type y) const {
			if (x < width_ && y < height_) {
				return data_[(y << POW2_POLICY) + x].tile.chr;
			}
			return NUL;
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

		inline bool is_locked() {
			return locked_;
		}

		uint8_t load(std::string file_path) {
			std::ifstream fis(file_path.c_str());
			if (!fis.is_open()) {
				std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';
				return 0;
			}
			char chr;
			for (size_type i = 0; i < size_; ++i) {
				fis.read(&chr, 1);
				if (fis.eof()) break;
				data_[i].tile.chr = chr;
			}
			return 1;
		}

		inline void lock() {
			locked_ = true;
		}

		void reveal(size_type x, size_type y) {
			if (x < width_ && y < height_) {
				data_[(y<< POW2_POLICY) + x].tile.state = visible;
			}
		}

		void reveal_all() {
			for (size_type i = 0; i < size_; ++i) {
				data_[(y << POW2_POLICY) + x].tile.state = visible;
			}
		}

		void reveal_neighbours(size_type x, size_type y) {
			for (size_type i = 0; i < neighbour_count; i += 2) {
				reveal(x + neighbourhood[i], y + neighbourhood[i + 1]);
			}
		}

		inline size_type size() const {
			return size_;
		}

		inline void unlock() {
			locked_ = false;
		}

		inline size_type width() const {
			return width_;
		}

	private:

		size_type width_, height_, size_;
		value_type* data_;
		bool locked_;

	};

}

#endif