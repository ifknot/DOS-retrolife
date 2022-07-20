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
			bios::wait_key_ascii();
			mda::mode7::exit();
		}
		std::cout << "success!\n";
	}

}

#endif