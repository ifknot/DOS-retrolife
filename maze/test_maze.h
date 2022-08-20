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

#include "../retrolib/gfx/mda/mode7/mda_mode7.h"

#include "../retrolib/memory/size_t.h"

using namespace bios;
using namespace mda::mode7;
using namespace jtl;

template<jtl::size_t POW2_POLICY = 5>
class maze_t {

	static const char NUL = 0;

public:

	typedef jtl::size_t size_type;
	typedef int8_t value_type;

	maze_t() : 
		width_(1 << POW2_POLICY),
		height_(width_),
		size_(width_ * height_),
		visisble_data_(new value_type[size_]),
		hidden_data_(new value_type[size_])
	{}

	~maze_t() {
		delete[] visisble_data_;
		delete[] hidden_data_;
	}

	inline const value_type* data() {
		return visisble_data_;
	}

	inline size_type height() {
		return height_;
	}

	void hide_all() {
		for (size_type i = 0; i < size_, ++i) {
			visisble_data_[i] = NUL;
		}
	}

	void reveal(size_type x, size_type y) {
		size_type i = (y >> 5)
	}

	void reveal_all() {
		for (size_type i = 0; i < size_, ++i) {
			visisble_data_[i] = hidden_data_[i];
		}
	}

	inline size_type size() {
		return size_;
	}

	inline size_type width() {
		return width_;
	}

private:

	void build_maze() {

	}

	size_type width_, height_, size_;
	value_type* visisble_data_;
	value_type* hidden_data_;

};

namespace test_maze {

	typedef maze_t<> maze32x32_t;

	void run() {
		std::cout
			<< "Using video card "
			<< video_adapter_names[detect_video_adapter_type()] << "\n Mode "
			<< video_mode_names[get_video_state().mode] << "\n"
			<< "Switch to mode 7 and ENTER the maze...\n";
		wait_key_ascii();
		enter();
		{
			maze32x32_t m;
			std::cout << m.size() << ' ' << m.width() << ' ' << m.height() << '\n';
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
