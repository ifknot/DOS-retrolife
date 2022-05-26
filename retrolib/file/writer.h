/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      23.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef WRITER
#define WRITER

/*

Writer  append(char c)  It appends the specified character to this writer.
Writer  append(CharSequence csq)        It appends the specified character sequence to this writer
Writer  append(CharSequence csq, int start, int end)    It appends a subsequence of the specified character sequence to this writer.
abstract void   close() It closes the stream, flushing it first.
abstract void   flush() It flushes the stream.
void    write(char[] cbuf)      It writes an array of characters.
abstract void   write(char[] cbuf, int off, int len)    It writes a portion of an array of characters.
void    write(int c)    It writes a single character.
void    write(String str)       It writes a string.
void    write(String str, int off, int len)     It writes a portion of a string.

*/

namespace jtl {

    template< typename T>
    struct writer {

        //append(char c)  It appends the specified character to this writer.

        //append(CharSequence csq)        It appends the specified character sequence to this writer

        //append(CharSequence csq, int start, int end)    It appends a subsequence of the specified character sequence to this writer.

        /**
        *  @brief Flushes then closes this stream and releases any system resources associated with it. If the stream is already closed then invoking this method has no effect.
        */
        virtual void close() = 0;


        /**
        *  @brief  Whether this stream is ready to be read from.
        *  @retval  - true/false
        */
        virtual bool is_ready() = 0;


        virtual void flush() = 0;

        //void  write(char[] cbuf)      It writes an array of characters.

        //abstract void write(char[] cbuf, int off, int len)    It writes a portion of an array of characters.

        /**
        * @brief Writes a single type T.
        */
        virtual void write(const T datum) = 0;

        virtual uint16_t write(const T* data, const uint16_t size) = 0;

        //virtual bool write(T* data, const uint16_t size, uin16_t offset) = 0;

    };

}

#endif