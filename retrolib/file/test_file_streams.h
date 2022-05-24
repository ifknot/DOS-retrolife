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

#include "file_input_stream.h"

namespace test_file_streams {

        void run() {
                std::cout << "test_file_streams... ";
                //test file_input_stream
                {
                    jtl::file_input_stream<char> f("nofile.dat");
                }
                {
                    jtl::file_input_stream<char> f("resource/empty.dat");
                    assert(f.ready());
                    std::cout << f.read();
                }
                {
                    jtl::file_input_stream<char> f("resource/alphabet.dat");
                    assert(f.ready());
                    char data[10];
                    assert(f.read(data, 10) == 10);
                    assert(f.read(data, 10) == 10);
                    assert(f.read(data, 10) != 10);
                }
                {
                    jtl::file_input_stream<int> f("resource/ints.dat");
                    assert(f.ready());
                    int data[10];
                    assert(f.read(data, 10) == 10);
                }
                {
                    jtl::file_input_stream<uint16_t> f("resource/ints.dat");
                    assert(f.ready());
                    uint32_t data[5];
                    assert(f.read((uint16_t*)data, 10) == 10);
                    std::cout << std::hex;
                    for (int i = 0; i < 5; ++i) {
                        std::cout << data[i] << ' ';
                    }
                    std::cout << '\n';
                }
                std::cout << "success!\n";
        }

}

#endif