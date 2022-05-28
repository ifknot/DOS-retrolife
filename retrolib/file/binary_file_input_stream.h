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

#include "reader.h"

namespace jtl {

        class binary_file_input_stream : public reader<char> {

        public:

            binary_file_input_stream(std::string file_path) :
                f(new std::ifstream(file_path.c_str(), f->binary))
            {
                if (!f->is_open()) {
                    std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';
                }
            }

            virtual void close() {
                if (f->is_open()) {
                    f->close();
                }
            }

            virtual bool is_ready() {
                return f && f->is_open() && f->good();
            }

            virtual char read() {
                char byte;
                assert(read(&byte, 1) == 1);
                return byte;
            }

            virtual uint16_t read(char* data, const uint16_t size) {
                f->read(data, size);
                return f->gcount();
            }

            virtual uint16_t read(char* data, const uint16_t size, uint16_t offset) {
                f->read(data + offset, size);
                return f->gcount();
            }

            virtual void reset() {
                f->seekg(0);
            }

            virtual int size() {
                int size_ = -1;
                int mark = static_cast<int>(f->tellg());
                if (is_ready()) {
                    f->seekg(0, f->end);
                    size_ = static_cast<int>(f->tellg());
                    f->seekg(mark);
                }
                return size_;
            }

            virtual int skip(int n) {
                n -= static_cast<int>(f->tellg());
                f->seekg(n);
                return static_cast<int>(f->tellg());
            }

            ~binary_file_input_stream() {
                close();
                delete f;
            }

        private:

                std::ifstream* f;

        };

}

#endif