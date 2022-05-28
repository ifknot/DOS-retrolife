/**
 *
 *  @file      reader.h
 *  @brief     reader is an abstract class for reading type T streams
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef READER_H
#define READER_H

#include <stdint.h>

namespace jtl {

        template< typename T>
        struct reader {

                /**
                *  @brief Closes this stream and releases any system resources associated with it. If the stream is already closed then invoking this method has no effect.
                */
                virtual void close() = 0;

                /**
                *  @brief  Whether this stream is ready to be read from.
                *  @retval  - true/false
                */
                virtual bool is_ready() = 0;

                /**
                *  @brief Reads a single type T.
                *  @retval type T
                */
                virtual T read() = 0;

                /**
                *  @brief  Reads size number of T into an array.
                *  @param  data - pointer to an array of type T with at least size space available
                *  @note no bounds checking is performed
                *  @param  size - the number of type T items to read
                *  @retval uint16_t the number of items actually read
                */
                virtual uint16_t read(T* data, const uint16_t size) = 0;

                /**
                *  @brief  Reads size number of T into a portion of an array starting at offset.
                *  @param  data - pointer to an array of type T with at least size space available
                *  @note no bounds checking is performed
                *  @param  size - the number of type T items to read
                *  @param  offset - into the data array
                *  @retval uint16_t the number of items actually read
                */
                virtual uint16_t read(T* data, const uint16_t size, uint16_t offset) = 0;

                /**
                *  @brief Resets the stream.
                */
                virtual void reset() = 0;

                virtual int size() = 0;

                /**
                *  @brief  skips n items T along the stream.
                *  @param  n - items to skip
                *  @retval   - actual number skipped
                */
                virtual int skip(int n) = 0;

        };

}

#endif

/*

virtual void close() = 0;

virtual void mark() = 0;

virtual bool markable() = 0;

virtual T read() = 0;

virtual uint16_t read(T* data, const uint16_t size) = 0;

virtual bool read(T* data, const uint16_t size, uin16_t offset) = 0;

virtual bool ready() = 0;

virtual void reset() = 0;

virtual uint16_t skip(uint16_t n) = 0;

*/
