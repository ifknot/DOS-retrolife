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

namespace jtl {

        template<typename T>
        class file_input_stream : public reader<T> {

        public:

                file_input_stream(std::string file_path) {   
                    f = new std::ifstream(file_path.c_str());
                    if (!f->is_open()) {
                        ready_ = false;
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

                virtual T read() {
                    T datum;
                    assert(read(&datum, 1) == 1);                       
                    return datum;
                }

                virtual uint16_t read(T* data, const uint16_t size) {
                    for (uint16_t i = 0; i < size; ++i) {
                        if (f->eof()) {
                              return i;
                        }
                        f->operator>>(data[i]);
                    }
                    return size;
                }

                //virtual bool read(T* data, const uint16_t size, uin16_t offset) = 0;

                //virtual void reset() = 0;

                virtual int size() {
                    int size_ = 0;
                    if (is_ready()) {
                        f->seekg(0, f->end);
                        size_ = f->tellg();
                        f->seekg(0);
                    }
                }

                //virtual uint16_t skip(uint16_t n) = 0;

                ~file_input_stream() {
                    close();
                    delete f;
                }

        private:

                std::ifstream* f;

        };

}

#endif