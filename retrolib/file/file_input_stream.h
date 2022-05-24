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

#include "..\jtl\unique_ptr.h"

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
                            delete f;
                        }
                        else {
                            ready_ = true;
                        }
                }

                virtual void close() {
                        if (f->is_open()) {
                                f->close();
                        }
                        ready_ = false;
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
#ifndef NDEBUG
                            std::cout << '\n';
#endif
                            return i;
                        }
                        f->operator>>(data[i]);
#ifndef NDEBUG
                        std::cout << data[i] << ' ';
#endif
                    }
#ifndef NDEBUG
                    std::cout << '\n';
#endif
                    return size;
                }

                //virtual bool read(T* data, const uint16_t size, uin16_t offset) = 0;

                virtual bool ready() {
                        return ready_;
                }

                //virtual void reset() = 0;

                //virtual uint16_t skip(uint16_t n) = 0;

                ~file_input_stream() {
                    if(f) {
                        close();
                        delete f;
                    }
                }

        private:

                std::ifstream* f;
                bool ready_;

        };

}

#endif