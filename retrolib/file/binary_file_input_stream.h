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

            binary_file_input_stream(std::string file_path) {
                f = new std::ifstream(file_path.c_str(), f->binary);
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

            virtual void mark() {}

            virtual bool markable() {
                return false;
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

            //virtual bool read(T* data, const uint16_t size, uin16_t offset) = 0;

            //virtual void reset() = 0;

            virtual int size() {
                int size_ = 0;
                if (is_ready()) {
                    f->seekg(0, f->end);
                    size_ = static_cast<int>(f->tellg());
                    f->seekg(0);
                }
                return size_;
            }

            //virtual uint16_t skip(uint16_t n) = 0;

            ~binary_file_input_stream() {
                close();
                delete f;
            }

        private:

                std::ifstream* f;

        };

}

#endif