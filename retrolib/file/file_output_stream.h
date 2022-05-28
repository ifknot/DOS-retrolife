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

        public:

        file_output_stream(std::string file_path, bool append = false) :
            sep_(' '),
            f((append)
                ? new std::ofstream(file_path.c_str(), f->app)
                : new std::ofstream(file_path.c_str())
            )
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

        virtual void flush() {
            f->flush();
        }

        virtual bool is_ready() {
            return f && f->open() && f->good();
        }

        virtual void reset() {
            f->seekp(0);
        }

        char seperator() {
            return sep_;
        }

        void seperator(const char sep) {
            sep_ = sep;
        }

        virtual int size() {
            int size_ = -1;
            int mark = static_cast<int>(f->tellp());
            if (is_ready()) {
                f->seekp(0, f->end);
                size_ = static_cast<int>(f->tellp());
                f->seekp(mark);
            }
            return size_;
        }

        virtual void write(const T datum) {
            write(&datum, 1);
        }

        virtual void write(const T* data, const uint16_t size) {
            write(data, size, 0);
        }

        virtual void write(const T* data, const uint16_t size, uint16_t offset) {
            for(uint16_t i = 0; i < size; ++i) {
                f->operator<<(data[offset + i]);
                f->put(seperator());
            }
            assert(f->good());
        }

        ~file_output_stream() {
            close();
            delete f;
        }

        protected:

            char sep_;
            std::ofstream* f;

        };

}

#endif