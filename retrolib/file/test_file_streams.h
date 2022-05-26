/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      24.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_FILE_STREAMS
#define TEST_FILE_STREAMS

#include <cassert>
#include <string>


#include "binary_file_input_stream.h"
#include "binary_file_output_stream.h"
#include "file_input_stream.h"

#define T1

namespace test_file_streams {

        void run() {
                std::cout << "test_file_streams... ";
#ifdef T1
                {
                    std::cout << "\ntest binary_file_output_stream\n";
                    {
                        jtl::binary_file_output_stream f("none/test.dat");
                        std::cout << std::dec << f.size() << '\n';
                    }
                    {
                        jtl::binary_file_output_stream f("resource/test.dat");
                        assert(f.is_ready());
                        std::cout << std::dec << f.size() << '\n';
                        f.write('A');
                        std::cout << std::dec << f.size() << '\n';
                    }
                }
#endif
#ifdef T2       
                {
                    std::cout << "\ntest binary_file_input_stream\n";
                    {
                        jtl::binary_file_input_stream f("nofile.dat");
                        std::cout << std::dec << f.size() << '\n';
                    }
                    {
                        jtl::binary_file_input_stream f("resource/empty.dat");
                        assert(f.is_ready());
                        std::cout << std::dec << f.size() << '\n';
                        //std::cout << f.read();
                        // yes assert panic
                    }
                    {
                        jtl::binary_file_input_stream f("resource/alphabet.dat");
                        assert(f.is_ready());
                        std::cout << std::dec << f.size() << '\n';
                        std::cout << f.read() <<'\n';
                    }
                    {
                        jtl::binary_file_input_stream f("resource/alphabet.dat");
                        assert(f.is_ready());
                        std::cout << std::dec << f.size() << '\n';
                        char data[20];
                        assert(f.read(data, 10) == 10);
                        for (int i = 0; i < 10; ++i) {
                            std::cout << (int)data[i] << ' ';
                        }
                        std::cout << '\n';
                        assert(f.read(data, 18) == 18);
                        std::cout << f.read(data, 10) << '\n';
                    }
                    {
                        jtl::binary_file_input_stream f("resource/hex.dat");
                        assert(f.is_ready());
                        std::cout << std::dec << f.size() << '\n';
                        char data[20];
                        assert(f.read(data, 10) == 10);
                        for (int i = 0; i < 10; ++i) {
                            std::cout << (int)data[i] << ' ';
                        }
                        std::cout << '\n';
                    }
                }
#endif
#ifdef T3 
#endif
#ifdef T4              
                {
                std::cout << "\ntest file_input_stream\n";
                    {
                        jtl::file_input_stream<char> f("nofile.dat");
                    }
                    {
                        jtl::file_input_stream<char> f("resource/empty.dat");
                        assert(f.is_ready());
                        std::cout << f.read(); // why no assert panic?
                    }
                    {
                        jtl::file_input_stream<char> f("resource/alphabet.dat");
                        assert(f.is_ready());
                        char data[10];
                        assert(f.read(data, 10) == 10);
                        assert(f.read(data, 10) == 10);
                        assert(f.read(data, 10) != 10);
                    }
                    {
                        jtl::file_input_stream<int> f("resource/ints.dat");
                        assert(f.is_ready());
                        int data[10];
                        assert(f.read(data, 10) == 10);
                    }
                    {
                        jtl::file_input_stream<uint16_t> f("resource/ints.dat");
                        assert(f.is_ready());
                        uint32_t data[5];
                        assert(f.read((uint16_t*)data, 10) == 10);
                        std::cout << std::hex;
                        for (int i = 0; i < 5; ++i) {
                            std::cout << data[i] << ' ';
                        }
                        std::cout << '\n';
                    }
                }
#endif
                std::cout << "success!\n";
        }

}

#endif