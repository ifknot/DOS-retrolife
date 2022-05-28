/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      24.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef BINARY_FILE_INPUT_STREAM_H
#define BINARY_FILE_INPUT_STREAM_H

#include <cassert>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>

#include "..\dos\dos_error_messages.h"

#include "file_input_stream.h"

namespace jtp {

        struct binary_file_input_stream : public file_input_stream<char> {

            binary_file_input_stream(std::string file_path) : file_input_stream<char>(file_path) {}

            virtual char read() {
                char byte;
                assert(read(&byte, 1) == 1);
                return byte;
            }

            virtual uint16_t read(char* data, const uint16_t size) {
                return read(data, size, 0);
            }

            virtual uint16_t read(char* data, const uint16_t size, uint16_t offset) {
                f->read(data + offset, size);
                return f->gcount();
            }

        };

}

#endif