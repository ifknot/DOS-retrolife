
#include <iostream>
#include <stdint.h>
#include <vector>

#include "retrolib/gfx/hga/test_hga.h"

#include "retrolib/dos/dos_segmented_memory_block.h"

int main() {
  std::cout << "Conway's Game of Life...\n";

  dos::segmented_memory_block<uint8_t> cells8(16);
  cells8.fill('A');
  cells8.dump();
  std::cout << "capacity " << cells8.capacity() << '\n'
	  << "bytes " << cells8.bytes() << '\n'
	  << "paragraphs " << cells8.paragraphs() << '\n';

  dos::segmented_memory_block<uint16_t> cells16(16);
  cells16.fill(0x4142);
  cells16.dump();
  std::cout << std::hex << cells16[15] << '\n';
  std::cout << "capacity " << cells16.capacity() << '\n'
	  << "bytes " << cells16.bytes() << '\n'
	  << "paragraphs " << cells16.paragraphs() << '\n';

  dos::segmented_memory_block<uint32_t> cells32(16);
  cells32.fill(0x41424344);
  cells32.dump();
  std::cout << std::hex << cells32[15] << '\n';
  std::cout << "capacity " << cells32.capacity() << '\n'
	  << "bytes " << cells32.bytes() << '\n'
	  << "paragraphs " << cells32.paragraphs() << '\n';
  

  //test_hga::run();
  

}
