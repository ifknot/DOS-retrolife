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
#include "mda_mode7_cls.h"

using namespace bios;
using namespace mda::mode7;
using namespace  attribute;

namespace test_mode7 {

	void run() {

		std::cout
			<< bios::video_adapter_names[bios::detect_video_adapter_type()] << "\n"
			<< bios::video_mode_names[bios::get_video_state().mode] << "\n"
			<< "test IBM Monochrome Display Adapter (MDA)...\n";
		wait_key_ascii();
		enter();
		std::cout << "mode " << bios::video_mode_names[bios::get_video_state().mode] << "\n";
		/* {
			
			std::cout << (char) colour::gray << std::endl;

			screen_bound::plot_character(10, 10, 'A');
			screen_bound::plot_character(10, 11, 'A', invisible);
			screen_bound::plot_character(10, 12, 'A', underline);
			screen_bound::plot_character(10, 13, 'A', normal);
			screen_bound::plot_character(10, 14, 'A', bright);
			screen_bound::plot_character(10, 15, 'A', blink);
			screen_bound::plot_character(10, 16, 'A', reverse);
			screen_bound::plot_character(10, 17, 'A', reverse_bright);
			screen_bound::plot_character(10, 18, 'A', reverse_blink);
			screen_bound::plot_character(10, 19, 'A', bright_blink);
			wait_key_ascii();
			screen_bound::plot_attribute(10, 11, 'A', bright_blink);
			wait_key_ascii();
			cls_attributes();
			wait_key_ascii();
			cls_attributes(blink);
			wait_key_ascii();
			cls_characters('*');
			wait_key_ascii();
			cls();
			wait_key_ascii();
		}*/
		{
			cls();
			wait_key_ascii();
		}
		exit();
		std::cout << "mode " << bios::video_mode_names[bios::get_video_state().mode] << "\n";
		std::cout << "success!\n";
	}

}

#endif