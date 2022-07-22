/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      20.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_MODE7_H
#define TEST_MODE7_H

#include <iostream>
#include <cassert>

#include "../../../bios/bios_services.h"

#include "mda_mode7.h"
#include "mda_mode7_plot_point.h"

using namespace mda::mode7::attribute;

namespace test_mode7 {

	void run() {

		std::cout
			<< bios::video_adapter_names[bios::detect_video_adapter_type()] << "\n"
			<< bios::video_mode_names[bios::get_video_state().mode] << "\n"
			<< "test IBM Monochrome Display Adapter (MDA)...\n";
		{
			bios::wait_key_ascii();
			mda::mode7::enter();
			std::cout << bios::video_mode_names[bios::get_video_state().mode] << "\n";
			std::cout << (char)mda::mode7::colour::gray << std::endl;

			mda::mode7::screen_bound::plot_character(10, 10, 'A');
			mda::mode7::screen_bound::plot_character(10, 11, 'A', invisible);
			mda::mode7::screen_bound::plot_character(10, 12, 'A', underline);
			mda::mode7::screen_bound::plot_character(10, 13, 'A', normal);
			mda::mode7::screen_bound::plot_character(10, 14, 'A', bright);
			mda::mode7::screen_bound::plot_character(10, 15, 'A', blink);
			mda::mode7::screen_bound::plot_character(10, 16, 'A', reverse);
			mda::mode7::screen_bound::plot_character(10, 17, 'A', reverse_bright);
			mda::mode7::screen_bound::plot_character(10, 18, 'A', reverse_blink);
			mda::mode7::screen_bound::plot_character(10, 19, 'A', bright_blink);
			bios::wait_key_ascii();
			mda::mode7::screen_bound::plot_attribute(10, 11, 'A', bright_blink);
			bios::wait_key_ascii();
			mda::mode7::exit();
		}
		std::cout << "success!\n";
	}

}

#endif