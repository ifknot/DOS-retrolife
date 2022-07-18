/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_VGA_H
#define TEST_VGA_H

#include <iostream>
#include <cassert>
#include <cmath>
#include <stdio.h>

#include "../../bios/bios_services.h"

namespace test_vga {

	void run() {
		std::cout
			<< bios::video_adapter_names[bios::detect_video_adapter_type()] << " "
			<< "\ntest VGA...\n";
		{
			
		}
		std::cout << "success!\n";
	}

}

#endif