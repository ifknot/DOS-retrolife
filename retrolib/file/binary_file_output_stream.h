/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      26.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef BINARY_FILE_OUTPUT_STREAM_H
#define BINARY_FILE_OUTPUT_STREAM_H

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>

#include "..\dos\dos_error_messages.h"

#include "file_output_stream.h"

namespace jtp {

        struct binary_file_output_stream : public file_output_stream<char> {

            binary_file_output_stream(std::string file_path, bool append = false) : file_output_stream<char>(file_path, append) {}

            void write(const char byte) {
                write(&byte, 1);

            }

            void write(const char* data, const uint16_t size) {
                write(data, size, 0);
            }

            void write(const char* data, const uint16_t size, uint16_t offset) {
                f->write(data + offset, size);
                assert(f->good());
            }


        };

}

#endif