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
		*  @brief Marks the present position in the stream.
		*/
		virtual void mark() = 0;
		
		/**
		*  @brief  whether this stream supports the mark() operation.
		*  @retval  - true/false
		*/
		virtual bool markable() = 0;
		
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
		*  @brief  Functor wrapper for read(T* data, const uint16_t size)
		*/
		inline uint16_t operator()(T* data, const uint16_t size) {
			read(data, size);
		}

		/**
		*  @brief  Reads size number of T into a portion of an array starting at offset.		
		*  @param  data - pointer to an array of type T with at least size space available
		*  @note no bounds checking is performed 
		*  @param  size - the number of type T items to read
		*  @param  offset - into the data array
		*  @retval uint16_t the number of items actually read 
		*/
		virtual bool read(T* data, const uint16_t size, uin16_t offset) = 0;
		
		/**
		*  @brief  Functor wrapper for read(T* data, const uint16_t size, uin16_t offset)
		*/
		inline bool operator()(T* data, const uint16_t size, uin16_t offset) {	//functor version
			read(data, size, offset);
		}

		/**
		*  @brief  Whether this stream is ready to be read.
		*  @retval  - true/false
		*/
		virtual bool ready() = 0;
		
		/**
		*  @brief Resets the stream.
		*/
		virtual void reset() = 0;		
		
		/**
		*  @brief  skips n items T along the stream.
		*  @param  n - items to skip
		*  @retval   - actual number skipped
		*/
		virtual uint16_t skip(uint16_t n) = 0;		

		virtual ~reader() {}

	};

}

#endif


