/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      24.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef FILE_INPUT_STREAM_H
#define FILE_INPUT_STREAM_H

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "..\dos\dos_error_messages.h"

#include "reader.h"

namespace jtp {

        template<typename T>
        class file_input_stream : public reader<T> {

        public:

                file_input_stream(std::string file_path) :
                    f(new std::ifstream(file_path.c_str()))
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

                virtual T read() {
                    T datum;
                    assert(read(&datum, 1) == 1);
                    return datum;
                }

                virtual uint16_t read(T* data, const uint16_t size) {
                    return read(data, size, 0);
                }

                virtual uint16_t read(T* data, const uint16_t size, const uint16_t offset) {
                    for (uint16_t i = 0; i < size; ++i) {
                        if (f->eof()) {
                            return i - 1;
                        }
                        f->operator>>(data[offset + i]);
                    }
                    return size;
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

                ~file_input_stream() {
                    close();
                    delete f;
                }

        protected:

                std::ifstream* f;

        };

}

#endif