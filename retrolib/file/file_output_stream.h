/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef FILE_OUTPUT_STREAM_H
#define FILE_OUTPUT_STREAM_H

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>

#include "..\dos\dos_error_messages.h"

#include "writer.h"

namespace jtp {

	template<typename T>
	class file_output_stream : public writer<T> {

	};

}

#endif