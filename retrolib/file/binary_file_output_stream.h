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

#include "writer.h"

namespace jtl {

        class binary_file_output_stream : public writer<char> {

        public:

            binary_file_output_stream(std::string file_path, bool append = false) {
                if (append) {
                    f = new std::ofstream(file_path.c_str(), f->app | f->binary);
                }
                else {
                    f = new std::ofstream(file_path.c_str());
                }
                if (!f->is_open()) {
                    std::cerr << dos::error::messages[dos::error::FILE_NOT_FOUND] << file_path.c_str() << '\n';
                }
            }

            virtual void close() {
                if (f->is_open()) {
                    f->flush();
                    f->close();
                }
            }

            virtual bool is_ready() {
                return f && f->is_open() && f->good();
            }

            virtual void flush() {
                f->flush();
            }

            virtual int size() {
                int size_ = -1;
                if (is_ready()) {
                    f->seekp(0, f->end);
                    size_ = static_cast<int>(f->tellp());
                    f->seekp(0);
                }
                return size_;
            }

            virtual void write(char byte) {
                write(&byte, 1);
                assert(f->good());
            }

            virtual void write(const char* data, const uint16_t size) {
                f->write(data, size);
                assert(f->good());
            }

            ~binary_file_output_stream() {
                    close();
                    delete f;
            }

        private:

                std::ofstream* f;

        };

}

#endif