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
		int	read()	It reads a single character.
			int	read(char[] cbuf)	It reads characters into an array.
			abstract int	read(char[] cbuf, int off, int len)	It reads characters into a portion of an array.
			int	read(CharBuffer target)	It attempts to read characters into the specified character buffer.
			boolean	ready()	It tells whether this stream is ready to be read.
			void	reset()	It resets the stream.
			long	skip(long n)	It skips characters.*/


		virtual T read() = 0

		/**
		*  @brief	Attempts to read size number of type T into the specified data buffer.
		*  @warning No bounds checking!
		*  @note	maximum 64K types T 
		*  @note	
		*  @param  data<T>[]	destination buffer 
		*  @param  size			number of elements type T (max 64K)
		*  @retval				true on successful read, false on any fail
		*/

		virtual bool read(T* data, const uint16_t size) = 0;


		inline bool operator()(T* data, const uint16_t size) {
			read(data, size);
		}

		virtual ~reader() {}


		template<typename T>
		void DynamicArray<T>::push_back(const T& value)
		{
			if (m_length == m_capacity)
			{
				m_capacity *= 2;

				T* tmpArray = new T[m_capacity];

				for (int i = 0; i < m_length; ++i)
				{
					tmpArray[i] = m_data[i];
				}
				delete[] m_data;
				m_data = tmpArray;
			}
			m_data[m_length] = value;
			m_length++;
		}

	};

}

#endif


