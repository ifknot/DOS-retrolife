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

		virtual void close() = 0;		// closes the stream and releases any system resources associated with it.
		
		virtual void mark() = 0;		// marks the present position in the stream.
		
		virtual bool markable() = 0;	// whether this stream supports the mark() operation.
		
		virtual T read() = 0;			// reads a single type T.
		
		virtual bool read(T* data, const uint16_t size) = 0;	// reads size number of T into an array.
		
		inline bool operator()(T* data, const uint16_t size) {	// functor version
			read(data, size);
		}

		virtual bool read(T* data, const uint16_t size, uin16_t offset) = 0;	// reads size number of T into a portion of an array starting at offset.		
		
		inline bool operator()(T* data, const uint16_t size, uin16_t offset) {	//functor version
			read(data, size, offset);
		}
		virtual bool ready() = 0;		// whether this stream is ready to be read.
		
		virtual void reset() = 0;		// resets the stream.
		
		virtual uint16_t skip(uint16_t n) = 0;		// skips n items T.

		virtual ~reader() {}

	};

}

#endif


